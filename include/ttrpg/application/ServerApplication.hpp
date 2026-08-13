#pragma once

#include <ttrpg/network/Server.hpp>
#include <ttrpg/ui/server/ServerUI.hpp>

namespace ttrpg::application {
    class ServerApplication {
    public:
        ServerApplication();

        void run();
    private:
        ttrpg::network::Server server;
        ttrpg::ui::server::ServerUI ui;
    };
}