#pragma once

#include <ttrpg/chat/ChatRoom.hpp>
#include <ttrpg/command/ServerCommandHandler.hpp>
#include <ttrpg/util/Logger.hpp>

#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include <asio.hpp>

namespace ttrpg::network {
    class Server {
    public:
        using MessageCallback = std::function<void(const std::string&)>;

        explicit Server(MessageCallback onMessage);

        void start();

        void sendCommand(const std::string& message);
    private:
        void acceptConnection();

        void removeConnection(std::shared_ptr<class Connection> connection);

        void handleMessage(std::shared_ptr<class Connection> connection, const ttrpg::network::Message& message);

        asio::io_context io;
        asio::ip::tcp::acceptor acceptor;

        MessageCallback onMessage;

        std::vector<std::shared_ptr<class Connection>> connections;

        ttrpg::chat::ChatRoom chatRoom;
        ttrpg::util::Logger logger;
        ttrpg::command::ServerCommandHandler commandHandler;
    };
} 

