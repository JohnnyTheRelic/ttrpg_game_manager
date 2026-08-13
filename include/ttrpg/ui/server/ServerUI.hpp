#pragma once

#include <functional>
#include <string>
#include <vector>

#include <ftxui/component/screen_interactive.hpp>

namespace ttrpg::ui::server {
    class ServerUI {
    public:
        using SendCommandCallback = std::function<void(const std::string&)>;

        explicit ServerUI(SendCommandCallback onSendCommand);

        void run();

        void addServerMessage(const std::string& message);

    private:
        void handleSendCommand(const std::string& command);

        std::vector<std::string> messages;
        std::string input;

        SendCommandCallback onSendCommand;

        ftxui::ScreenInteractive screen;

        ftxui::Component commandInput;
        ftxui::Component sendButton;
        ftxui::Component container;

        ftxui::Component root;

    };
}