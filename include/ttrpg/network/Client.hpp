#pragma once

#include <QString>

#include <functional>
#include <iostream>
#include <asio.hpp>
#include <array>

#include <ttrpg/user/User.hpp>

namespace ttrpg::network {
    class Client {
    public:
        using MessageCallback = std::function<void(const QString&)>;

        explicit Client(MessageCallback onMessage);

        void run();
        void connect();
        void registerUser(const ttrpg::user::User& user);
        void sendMessage(const QString& message);
        void receiveMessages();
        void disconnect();
    private:
        asio::io_context io;
        asio::ip::tcp::socket socket;
        std::array<char, 1024> buffer;

        MessageCallback onMessage;
    };
}