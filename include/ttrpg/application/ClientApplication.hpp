#pragma once

#include <ttrpg/network/Client.hpp>
#include <ttrpg/ui/client/ClientUI.hpp>
#include <ttrpg/user/User.hpp>

#include <thread>

namespace ttrpg::application {
    class ClientApplication {
    public:
        ClientApplication();

        void run();
    private:
        void handleLogin(const std::string& username);

        void runChat(const ttrpg::user::User& user);

        ttrpg::network::Client client;
        ttrpg::ui::client::ClientUI ui;
    };
}