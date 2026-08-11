#pragma once

#include <string>

namespace ttrpg::network {
    class Server;
}

namespace ttrpg::command {
    class ServerCommandHandler {
    public:
        explicit ServerCommandHandler(ttrpg::network::Server& server);

        bool handle(const std::string& command);

    private:
        ttrpg::network::Server& server;

        void help();
        void users();
        void quit();
    };
}