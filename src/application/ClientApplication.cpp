#include <ttrpg/application/ClientApplication.hpp>

#include <ttrpg/user/User.hpp>

#include <functional>
#include <utility>
#include <thread>
#include <iostream>
#include <string>

namespace ttrpg::application {
    ClientApplication::ClientApplication() : ui([this](const std::string& username) {
        handleLogin(username);
    }) {}

    void ClientApplication::run() {
        ui.run();
    }

    void ClientApplication::handleLogin(const std::string& username) {
        try {
            ttrpg::user::User user(username);

            client.connect();
            client.registerUser(user);
            client.receiveMessages(); // Start receiving messages in the background

            std::thread networkThread([this]() {
                client.run(); // Run the io_context in a separate thread
            });

            runChat(user);

            networkThread.join(); // Wait for the network thread to finish
        } catch (const std::invalid_argument& exception) {
            std::cerr << "Invalid Username: " << exception.what() << std::endl;
        }
    }

    void ClientApplication::runChat(const ttrpg::user::User& user) {
        std::string message;

        std::cout << "Connected to chat as " << user.getUsername() << ". Type your messages below (type '/quit' to quit):" << std::endl;

        while(true) {
            std::cout << "> " << std::flush;
            std::getline(std::cin >> std::ws, message);

            if(message == "/quit") {
                client.disconnect();
                break;
            }

            if(message.empty()) {
                continue; // Skip sending empty messages
            }

            client.sendMessage(message);
        }
    }
}