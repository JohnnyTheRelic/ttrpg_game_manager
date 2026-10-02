#include <ttrpg/network/Client.hpp>
#include <ttrpg/network/Message.hpp>

#include <utility>

#include <QDebug>

namespace ttrpg::network {
    Client::Client(MessageCallback onMessage) : socket(io), onMessage(std::move(onMessage)) {

    }

    void Client::run() {
        io.run();
    }

    void Client::connect() {
        asio::error_code ec;

        asio::ip::tcp::endpoint endpoint(asio::ip::make_address("127.0.0.1", ec), 12345);

        if(ec) {
            qWarning() << "Failed to create endpoint: " << ec.message();
            return;
        }

        socket.connect(endpoint, ec);

        if(ec) {
            qWarning() << "Failed to connect to server: " << ec.message();
            return;
        }

        qDebug() << "Connected to server at " << endpoint.address().to_string() << ":" << endpoint.port();
    }

    void Client::registerUser(const ttrpg::user::User& user) {
        asio::error_code ec;

        ttrpg::network::Message registrationMessage(ttrpg::network::MessageType::Registration, user.getUsername());

        socket.write_some(asio::buffer(registrationMessage.serialize()), ec);

        if(ec) {
            qWarning() << "Failed to send user registration: " << ec.message();
            return;
        }

        qDebug() << "User registration sent: " << user.getUsername();
    }

    void Client::sendMessage(const QString& message) {
        asio::error_code ec;

        ttrpg::network::Message chatMessage(ttrpg::network::MessageType::ChatMessage, message);

        socket.write_some(asio::buffer(chatMessage.serialize()), ec);

        if(ec) {
            qWarning() << "Failed to send message: " << ec.message();
            return;
        }
    }

    void Client::receiveMessages() {
        socket.async_read_some(asio::buffer(buffer), [this](const asio::error_code ec, std::size_t bytes_received) {
            if (!ec) {
                std::string proto(buffer.data(), bytes_received);
                
                try {
                    const Message message = Message::deserialize(proto);

                    if(onMessage) {
                        onMessage(message.getContent());
                    }
                }
                catch (const std::exception& exception) {
                    qWarning() << "Rejected invalid network message: " << exception.what();
                }
                
                // Continue receiving data
                receiveMessages();
            } else {
                qWarning() << "Error receiving data: " << ec.message();
            }
        });
    }

    void Client::disconnect() {
        asio::error_code ec;
        socket.shutdown(asio::ip::tcp::socket::shutdown_both, ec);
        socket.close(ec);

        if(ec) {
            qWarning() << "Failed to disconnect: " << ec.message();
            return;
        }

        io.stop();

        qDebug() << "Disconnected from server.";
    }
}