#include <ttrpg/ui/client/ClientUI.hpp>
#include <ttrpg/ui/client/LoginScene.hpp>

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

#include <utility>
#include <iostream>

namespace ttrpg::ui::client {
    ClientUI::ClientUI(LoginCallback onLogin) : screen(ftxui::ScreenInteractive::Fullscreen()), onLogin(std::move(onLogin)) {}

    void ClientUI::run() {
        LoginScene loginScene(screen, [this](const std::string& username) {
            handleLogin(username);
        });

        auto component = loginScene.component();

        screen.Loop(component);
    }

    void ClientUI::handleLogin(const std::string& username) {
        onLogin(username);
    }
}