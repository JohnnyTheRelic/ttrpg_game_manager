#pragma once

#include <ttrpg/chat/ChatRoom.hpp>
#include <ttrpg/util/Logger.hpp>

#include <iostream>
#include <memory>
#include <vector>
#include <asio.hpp>

namespace ttrpg::network {
    class Server {
    public:
        Server();

        void start();
    private:
        void acceptConnection();

        void removeConnection(std::shared_ptr<class Connection> connection);

        void handleMessage(std::shared_ptr<class Connection> connection, const ttrpg::network::Message& message);

        asio::io_context io;
        asio::ip::tcp::acceptor acceptor;

        std::vector<std::shared_ptr<class Connection>> connections;

        ttrpg::chat::ChatRoom chatRoom;
        ttrpg::util::Logger logger;
    };
} 