#pragma once

#include <ttrpg/ui/client/LoginScene.hpp>
#include <ttrpg/ui/client/ChatScene.hpp>

#include <functional>
#include <string>

#include <ftxui/component/screen_interactive.hpp>

namespace ttrpg::ui::client {
    class ClientUI {
    public:
        using LoginCallback = std::function<void(const std::string&)>;
        using SendMessageCallback = std::function<void(const std::string&)>;

        explicit ClientUI(LoginCallback onLogin, SendMessageCallback onSendMessage);

        void run();

        void showChat();

        void addChatMessage(const std::string& message);

    private:
        int currentScene = 0;

        void handleLogin(const std::string& username);
        void handleSendMessage(const std::string& message);

        LoginCallback onLogin;
        SendMessageCallback onSendMessage;

        ftxui::ScreenInteractive screen;
        
        std::unique_ptr<LoginScene> loginScene;
        std::unique_ptr<ChatScene> chatScene;

        ftxui::Component root;
    };
}