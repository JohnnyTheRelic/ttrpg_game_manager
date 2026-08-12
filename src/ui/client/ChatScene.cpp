#include <ttrpg/ui/client/ChatScene.hpp>

#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

#include <utility>
#include <iostream>

namespace ttrpg::ui::client {
    ChatScene::ChatScene(SendMessageCallback onSendMessage) : onSendMessage(std::move(onSendMessage)) {
        using namespace ftxui;

        messageInput = Input(&input, "Message");

        sendButton = Button("Send", [this] {
            if(!input.empty()) {
                this->onSendMessage(input);
                input.clear();
            }
        });

        container = Container::Horizontal({
            messageInput,
            sendButton
        });

        root = Renderer(container, [this] {
            Elements messageElements;

            for(const auto& message : messages) {
                messageElements.push_back(text(message));
            }

            auto messageArea = vbox(messageElements) | frame | flex;

            return vbox({
                text("T T R P G") | bold | center,
                separator(),
                messageArea,
                separator(),
                hbox({
                    text("> "),
                    messageInput->Render() | flex,
                    sendButton->Render()
                })
            }) | border;
        });
    }

    ftxui::Component ChatScene::component() {
        return root;
    }

    void ChatScene::addMessage(const std::string& message) {
        messages.push_back(message);
    }
}