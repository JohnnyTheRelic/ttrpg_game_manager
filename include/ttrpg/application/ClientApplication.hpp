#pragma once

#include <QObject>

#include <ttrpg/network/Client.hpp>
#include <ttrpg/ui/client/LoginWindow.hpp>
#include <ttrpg/user/User.hpp>

#include <thread>

namespace ttrpg::application {
    class ClientApplication : public QObject {
        Q_OBJECT
    public:
        ClientApplication();

        void run();
    signals:
        //void registerUser(const QString& username);
        void handleChatMessage(const QString& message);
    private slots:
        void handleLogin(const QString& username);
        //void handleChatMessage(const QString& message);
    private:
        network::Client client;
        LoginWindow login;
        //ttrpg::ui::client::ChatWindow chat;
    };
}