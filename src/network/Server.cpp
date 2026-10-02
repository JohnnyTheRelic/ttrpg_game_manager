#include <ttrpg/network/Connection.hpp>
#include <ttrpg/network/Message.hpp>
#include <ttrpg/network/Server.hpp>
#include <ttrpg/util/Time.hpp>
#include <ttrpg/util/String.hpp>

#include <algorithm>
#include <iostream>

namespace ttrpg::network {
    Server::Server(MessageCallback onMessage) : onMessage(std::move(onMessage)), acceptor(io, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 12345)), logger([this](const std::string& message) {
        this->onMessage(message);
    }), commandHandler(*this) {}

    void Server::start() {
        logger.info("Server started on port 12345");

        // Wait for a client to connect
        acceptConnection();

        io.run();
    }

    void Server::sendCommand(const std::string& command) {
        if(!commandHandler.handle(command)) {
            logger.warn("Unknown command: " + command);
        }
    }

    void Server::acceptConnection() {
        auto connection = std::make_shared<Connection>(io, [this](std::shared_ptr<Connection> connection) {
                removeConnection(connection);}, 
            [this](std::shared_ptr<Connection> connection, const ttrpg::network::Message& message) {
                handleMessage(connection, message);
        });

        acceptor.async_accept(connection->getSocket(), [this, connection](const asio::error_code ec) {
            if (!ec) {
                logger.info("Client connected from " + connection->getSocket().remote_endpoint().address().to_string() + ":" + std::to_string(connection->getSocket().remote_endpoint().port()));
            
                chatRoom.addConnection(connection);
                connection->startReceiving();
            } else {
                logger.error("Failed to accept connection: " + ec.message());
            }

            acceptConnection(); // Accept the next connection
        });
    }

    void Server::removeConnection(std::shared_ptr<Connection> connection) {
        if(connection->hasUser()) {
            logger.info("User" + ttrpg::util::toUtf8(connection->getUser().getUsername()) + " disconnected.");
        }
        else {
            logger.info("Unregistered user disconnected.");
        }
    }

    void Server::handleMessage(std::shared_ptr<Connection> connection, const ttrpg::network::Message& message) {
        switch (message.getType()) {
            case ttrpg::network::MessageType::Registration: {
                ttrpg::user::User user(message.getContent());
                connection->registerUser(user);

                const std::string userCode = ttrpg::util::toUtf8(user.getUsername());

                logger.info("User registered: " + userCode);
                chatRoom.broadcastMessage("User " + userCode + " has joined the chat.");
                break;}
            case ttrpg::network::MessageType::ChatMessage: {
                if(!connection->hasUser()) {
                    logger.error("Received chat message from unregistered user.");
                    return;
                }

                const std::string username = ttrpg::util::toUtf8(connection->getUser().getUsername());
                const std::string content = ttrpg::util::toUtf8(message.getContent());

                logger.chat(username + ": " + content);
                chatRoom.broadcastMessage(username + ": " + content);
                break; }
            default:
                logger.error("Unknown message type received.");
                break;
        }
    }
}
