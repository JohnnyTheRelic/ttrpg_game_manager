#include <ttrpg/ui/client/ClientUI.hpp>
#include <ttrpg/ui/client/LoginScene.hpp>
#include <ttrpg/ui/client/ChatScene.hpp>

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

#include <utility>
#include <iostream>

namespace ttrpg::ui::client {
    ClientUI::ClientUI(LoginCallback onLogin, SendMessageCallback onSendMessage) : screen(ftxui::ScreenInteractive::Fullscreen()), onLogin(std::move(onLogin)), onSendMessage(std::move(onSendMessage)) {
        loginScene = std::make_unique<LoginScene>(screen, [this](const std::string& username) {
            handleLogin(username);
        });

        chatScene = std::make_unique<ChatScene>([this](const std::string& message) {
            handleSendMessage(message);
        });

        root = ftxui::Container::Tab({
            loginScene->component(),
            chatScene->component()
        }, &currentScene);
    }

    void ClientUI::run() {
        using namespace ftxui;

        screen.Loop(root);
    }

    void ClientUI::showChat() {
        currentScene = 1;
    }

    void ClientUI::addChatMessage(const std::string& message) {
        screen.Post([this, message] {
            chatScene->addMessage(message);
        });
    }

    void ClientUI::handleLogin(const std::string& username) {
        onLogin(username);
    }

    void ClientUI::handleSendMessage(const std::string& message) {
        onSendMessage(message);
    }
}