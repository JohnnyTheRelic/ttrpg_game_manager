#pragma once

#include <functional>
#include <utility>
#include <string>

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

namespace ttrpg::ui::client {
    class LoginScene {
    public:
        using LoginCallback = std::function<void(const std::string&)>;

        LoginScene(ftxui::ScreenInteractive& screen, LoginCallback onLogin);

        ftxui::Component component();
        
    private:
        ftxui::ScreenInteractive& screen;
        LoginCallback onLogin;

        std::string username;

        ftxui::Component usernameInput;
        ftxui::Component submitButton;
        ftxui::Component container;
    };
}