#include <ttrpg/network/Client.hpp>
#include <ttrpg/network/Message.hpp>

#include <iostream>

namespace ttrpg::network {
    Client::Client() : socket(io) {}

    void Client::run() {
        io.run();
    }

    void Client::connect() {
        asio::error_code ec;

        asio::ip::tcp::endpoint endpoint(asio::ip::make_address("127.0.0.1", ec), 12345);

        if(ec) {
            std::cout << "Failed to create endpoint: " << ec.message() << std::endl;
            return;
        }

        socket.connect(endpoint, ec);

        if(ec) {
            std::cout << "Failed to connect to server: " << ec.message() << std::endl;
            return;
        }

        std::cout << "Connected to server at " << endpoint.address() << ":" << endpoint.port() << std::endl;
    }

    void Client::registerUser(const ttrpg::user::User& user) {
        asio::error_code ec;

        ttrpg::network::Message registrationMessage(ttrpg::network::MessageType::Registration, user.getUsername());

        socket.write_some(asio::buffer(registrationMessage.serialize()), ec);

        if(ec) {
            std::cout << "Failed to send user registration: " << ec.message() << std::endl;
            return;
        }

        std::cout << "User registration sent: " << user.getUsername() << std::endl;
    }

    void Client::sendMessage(const std::string& message) {
        asio::error_code ec;

        ttrpg::network::Message chatMessage(ttrpg::network::MessageType::ChatMessage, message);

        socket.write_some(asio::buffer(chatMessage.serialize()), ec);

        if(ec) {
            std::cout << "Failed to send message: " << ec.message() << std::endl;
            return;
        }
    }

    void Client::receiveMessages() {
        socket.async_read_some(asio::buffer(buffer), [this](const asio::error_code ec, std::size_t bytes_received) {
            if (!ec) {
                std::string message(buffer.data(), bytes_received);
                std::cout << message << std::endl;
                
                // Continue receiving data
                receiveMessages();
            } else {
                std::cout << "Error receiving data: " << ec.message() << std::endl;
            }
        });
    }

    void Client::disconnect() {
        asio::error_code ec;
        socket.shutdown(asio::ip::tcp::socket::shutdown_both, ec);
        socket.close(ec);

        if(ec) {
            std::cout << "Failed to disconnect: " << ec.message() << std::endl;
            return;
        }

        io.stop();

        std::cout << "Disconnected from server." << std::endl;
    }
}