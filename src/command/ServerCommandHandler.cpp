#include <ttrpg/command/ServerCommandHandler.hpp>
#include <ttrpg/network/Server.hpp>

namespace ttrpg::command {
    ServerCommandHandler::ServerCommandHandler(ttrpg::network::Server& server) : server(server) {}

    bool ServerCommandHandler::handle(const std::string& command) {
        if(command == "help") {
            help();
            return true;
        } else if(command == "users") {
            users();
            return true;
        } else if(command == "quit") {
            quit();
            return true;
        }
        return false;
    }

    void ServerCommandHandler::help() {
        std::cout << "Available commands:\n";
        std::cout << "  help  - Show this help message\n";
        std::cout << "  users - List connected users\n";
        std::cout << "  quit  - Quit the server\n";
    }

    void ServerCommandHandler::users() {
        // This function should list connected users.
        // Implementation depends on how the server manages connections and users.
        std::cout << "Listing connected users is not implemented yet.\n";
    }

    void ServerCommandHandler::quit() {
        std::cout << "Quitting the server...\n";
        // This function should signal the server to shut down.
        // Implementation depends on how the server handles shutdown.
    }
}