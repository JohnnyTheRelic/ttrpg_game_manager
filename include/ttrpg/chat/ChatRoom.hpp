#pragma once

#include <ttrpg/network/Connection.hpp>

#include <memory>
#include <vector>
#include <string>

namespace ttrpg::chat {
    class ChatRoom {
    public:
        void addConnection(std::shared_ptr<ttrpg::network::Connection> connection);

        void removeConnection(std::shared_ptr<ttrpg::network::Connection> connection);

        void broadcastMessage(const std::string& message);
    private:
        std::vector<std::shared_ptr<ttrpg::network::Connection>> connections;
    };
}