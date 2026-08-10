#pragma once

#include <ttrpg/network/Client.hpp>
#include <ttrpg/user/User.hpp>

#include <thread>

namespace ttrpg::application {
    class ClientApplication {
    public:
        void run();
    private:
        void runChat(const ttrpg::user::User& user);

        ttrpg::network::Client client;
    };
}