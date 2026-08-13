#include <ttrpg/application/ServerApplication.hpp>

namespace ttrpg::application {
    ServerApplication::ServerApplication() : server([this](const std::string& message) {
        ui.addServerMessage(message);
    }), ui([this](const std::string& command) {
        server.sendCommand(command);
    }) {}

    void ServerApplication::run() {
        std::thread serverThread([this]() {
            server.start();
        });

        ui.run();

        serverThread.join();
    }
}
