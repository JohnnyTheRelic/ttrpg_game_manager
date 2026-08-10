#include <ttrpg/network/Connection.hpp>
#include <ttrpg/util/Logger.hpp>
#include <ttrpg/util/Time.hpp>

#include <iostream>
#include <utility>

namespace ttrpg::network {
    Connection::Connection(asio::io_context& io, DisconnectHandler disconnectHandler, MessageHandler messageHandler) : 
        socket(io), disconnectHandler(std::move(disconnectHandler)), messageHandler(std::move(messageHandler)) {}

    asio::ip::tcp::socket& Connection::getSocket() {
        return socket;
    }

    const ttrpg::user::User& Connection::getUser() const {
        if(!user.has_value()) {
            throw std::runtime_error("User not registered");
        }
        return user.value();
    }

    void Connection::registerUser(const ttrpg::user::User& user) {
        this->user.emplace(user);
    }

    bool Connection::hasUser() const {
        return user.has_value();
    }

    void Connection::startReceiving() {
        socket.async_read_some(asio::buffer(buffer), [this](const asio::error_code ec, std::size_t bytes_received) {
            if (!ec) {
                std::string message(buffer, bytes_received);
                
                if(messageHandler) {
                    messageHandler(shared_from_this(), ttrpg::network::Message::deserialize(message));
                }

                // Continue receiving data
                startReceiving();
            } else {
                std::cout << "[" << ttrpg::util::currentTime() << "] [SERVER] Failed to receive message: " << ec.message() << std::endl;

                if(disconnectHandler) {
                    disconnectHandler(shared_from_this());
                }
            }
        });
    }

    void Connection::send(const std::string& message) {
        asio::error_code ec;
        socket.write_some(asio::buffer(message), ec);

        if(ec) {
            std::cout << "[" << ttrpg::util::currentTime() << "] [SERVER] Failed to send message: " << ec.message() << std::endl;
        } else {
            std::cout << "[" << ttrpg::util::currentTime() << "] [SERVER] Sent message: " << message << std::endl;
        }
    }
}