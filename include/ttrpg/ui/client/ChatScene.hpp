#pragma once

#include <functional>
#include <string>
#include <vector>

#include <ftxui/component/component.hpp>

namespace ttrpg::ui::client {
    class ChatScene {
    public:
        using SendMessageCallback = std::function<void(const std::string&)>;

        explicit ChatScene(SendMessageCallback onSendMessage);

        ftxui::Component component();

        void addMessage(const std::string& message);
    private:
        SendMessageCallback onSendMessage;

        std::vector<std::string> messages;
        std::string input;

        ftxui::Component root;

        ftxui::Component messageInput;
        ftxui::Component sendButton;
        ftxui::Component container;
    };
}