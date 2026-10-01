#include <ttrpg/application/ClientApplication.hpp>

#include <ttrpg/user/User.hpp>

#include <functional>
#include <utility>
#include <thread>

namespace ttrpg::application {
    ClientApplication::ClientApplication() : client([this](const QString& message) {
        emit handleChatMessage(message);
    }), login() {
        QObject::connect(&login, &LoginWindow::loginRequest, this, &ClientApplication::handleLogin);
    }

    void ClientApplication::run() {
        login.show();
    }

    void ClientApplication::handleLogin(const QString& username) {
        try {
            ttrpg::user::User user(username);

            client.connect();
            client.registerUser(user);
            client.receiveMessages(); // Start receiving messages in the background

            std::thread networkThread([this]() {
                client.run(); // Run the io_context in a separate thread
            });

            //ui.showChat();

            networkThread.detach(); // Wait for the network thread to finish
        } catch (const std::invalid_argument& exception) {
            qWarning() << "Invalid Username: " << exception.what();
            login.show();
        }
    }
}