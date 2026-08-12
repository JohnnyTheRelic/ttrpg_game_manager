#pragma once

#include <functional>
#include <iostream>
#include <asio.hpp>
#include <array>

#include <ttrpg/user/User.hpp>

namespace ttrpg::network {
    class Client {
    public:
        using MessageCallback = std::function<void(const std::string&)>;

        explicit Client(MessageCallback onMessage);

        void run();
        void connect();
        void registerUser(const ttrpg::user::User& user);
        void sendMessage(const std::string& message);
        void receiveMessages();
        void disconnect();
    private:
        asio::io_context io;
        asio::ip::tcp::socket socket;
        std::array<char, 1024> buffer;

        MessageCallback onMessage;
    };
}