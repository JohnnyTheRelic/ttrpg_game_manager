#pragma once

#include <ttrpg/network/Message.hpp>
#include <ttrpg/user/User.hpp>
#include <ttrpg/util/Logger.hpp>

#include <iostream>
#include <string>
#include <asio.hpp>
#include <optional>

namespace ttrpg::network {
    class Connection : public std::enable_shared_from_this<Connection> {
    public:
        using DisconnectHandler = std::function<void(std::shared_ptr<Connection>)>;
        using MessageHandler = std::function<void(std::shared_ptr<Connection>, const ttrpg::network::Message&)>;

        explicit Connection(asio::io_context& io, DisconnectHandler disconnectHandler, MessageHandler messageHandler);

        asio::ip::tcp::socket& getSocket();

        const ttrpg::user::User& getUser() const;

        void registerUser(const ttrpg::user::User& user);

        bool hasUser() const;

        void startReceiving();

        void send(const std::string& message);
    private:
        std::optional<ttrpg::user::User> user;
        asio::ip::tcp::socket socket;
        char buffer[1024];
        DisconnectHandler disconnectHandler;
        MessageHandler messageHandler;
    };
}