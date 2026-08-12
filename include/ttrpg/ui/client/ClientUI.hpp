#pragma once

#include <functional>
#include <string>

#include <ftxui/component/screen_interactive.hpp>

namespace ttrpg::ui::client {
    class ClientUI {
    public:
        using LoginCallback = std::function<void(const std::string&)>;

        explicit ClientUI(LoginCallback onLogin);

        void run();

    private:
        enum class Scene {
            Login,
            Chat
        };

        void handleLogin(const std::string& username);

        std::string testString;

        Scene currentScene = Scene::Login;
        LoginCallback onLogin;
        ftxui::ScreenInteractive screen;
    
    };
}