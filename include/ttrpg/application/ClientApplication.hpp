#pragma once

#include <QApplication>

#include <ttrpg/network/Client.hpp>
#include <ttrpg/ui/client/ClientUI.hpp>
#include <ttrpg/user/User.hpp>

#include <thread>

namespace ttrpg::application {
    class ClientApplication : public QApplication {
        Q_OBJECT
    public:
        ClientApplication();

        void run();
    private slots:
        void handleLogin(const QString& username);
    private:
        void runChat(const ttrpg::user::User& user);

        ttrpg::network::Client client;
        ttrpg::ui::client::ClientUI ui;
    };
}