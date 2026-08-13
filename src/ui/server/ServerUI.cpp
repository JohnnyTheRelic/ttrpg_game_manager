#include <ttrpg/ui/server/ServerUI.hpp>

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

#include <utility>
#include <iostream>

namespace ttrpg::ui::server {
    ServerUI::ServerUI(SendCommandCallback onSendCommand) : screen(ftxui::ScreenInteractive::Fullscreen()), onSendCommand(std::move(onSendCommand)) {
        using namespace ftxui;

        commandInput = Input(&input, "Message");

        sendButton = Button("Send", [this] {
            if(!input.empty()) {
                this->onSendCommand(input);
                input.clear();
            }
        });

        container = Container::Horizontal({
            commandInput,
            sendButton
        });

        root = Renderer(container, [this] {
            Elements messageElements;

            for(const auto& message : messages) {
                messageElements.push_back(text(message));
            }

            auto messageArea = vbox(messageElements) | frame | flex;

            return vbox({
                text("TTRPG Server") | bold,
                text("Connected"),
                separator(),
                messageArea,
                separator(),
                hbox({
                    text("> "),
                    commandInput->Render() | flex,
                    sendButton->Render()
                })
            }) | border;
        });
    }

    void ServerUI::run() {
        using namespace ftxui;

        screen.Loop(root);
    }

    void ServerUI::addServerMessage(const std::string& message) {
        messages.push_back(message);
    }

    void ServerUI::handleSendCommand(const std::string& command) {
        onSendCommand(command);
    }
}
