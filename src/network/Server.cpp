#include <ttrpg/network/Connection.hpp>
#include <ttrpg/network/Message.hpp>
#include <ttrpg/network/Server.hpp>
#include <ttrpg/util/Time.hpp>

#include <algorithm>
#include <iostream>

namespace ttrpg::network {
    Server::Server() : acceptor(io, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 12345)), logger(), commandHandler(*this) {}

    void Server::start() {
        logger.info("Server started on port 12345");

        // Wait for a client to connect
        acceptConnection();

        std::thread consoleThread([this]() {
            runConsole();
        });

        io.run();

        consoleThread.join();
    }

    void Server::runConsole() {
        std::string command;

        while(true) {
            std::cout << "> " << std::flush;
            std::getline(std::cin >> std::ws, command);

            if(command.empty()) {
                continue;
            }

            if(!commandHandler.handle(command)) {
                logger.warn("Unknown command: " + command);
            }
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
        chatRoom.removeConnection(connection);

        logger.info("User " + connection->getUser().getUsername() + " disconnected.");
    }

    void Server::handleMessage(std::shared_ptr<Connection> connection, const ttrpg::network::Message& message) {
        switch (message.getType()) {
            case ttrpg::network::MessageType::Registration: {
                ttrpg::user::User user(message.getContent());
                connection->registerUser(user);

                logger.info("User registered: " + user.getUsername());
                chatRoom.broadcastMessage("User " + user.getUsername() + " has joined the chat.");
                break;}
            case ttrpg::network::MessageType::ChatMessage: {
                if(!connection->hasUser()) {
                    logger.error("Received chat message from unregistered user.");
                    return;
                }

                std::string formattedMessage = connection->getUser().getUsername() + ": " + message.getContent();

                logger.chat(formattedMessage);
                chatRoom.broadcastMessage(formattedMessage);
                break; }
            default:
                logger.error("Unknown message type received.");
                break;
        }
    }
}
