#include <ttrpg/chat/ChatRoom.hpp>
#include <ttrpg/network/Message.hpp>

namespace ttrpg::chat {
    void ChatRoom::addConnection(std::shared_ptr<ttrpg::network::Connection> connection) {
        connections.push_back(connection);
    }

    void ChatRoom::removeConnection(std::shared_ptr<ttrpg::network::Connection> connection) {
        auto it = std::find(connections.begin(), connections.end(), connection);
        if (it != connections.end()) {
            connections.erase(it);
        }
    }

    void ChatRoom::broadcastMessage(const ttrpg::network::Message& message) {
        for (const auto& connection : connections) {
            asio::error_code ec;
            connection->send(message);

            if(ec) {
                std::cout << "Failed to send message to a client: " << ec.message() << std::endl;
            }
        }
    }
}