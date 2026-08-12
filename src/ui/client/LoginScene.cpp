#include <ttrpg/ui/client/LoginScene.hpp>

#include <ftxui/dom/elements.hpp>

namespace ttrpg::ui::client {
    LoginScene::LoginScene(ftxui::ScreenInteractive& screen, LoginCallback onLogin) : screen(screen), onLogin(std::move(onLogin)) {
        using namespace ftxui;

        usernameInput = Input(&username, "Username");

        submitButton = Button("Connect", [this] {
            if (!username.empty()) {
                this->onLogin(username);
            }
        });

        container = Container::Vertical({
            usernameInput,
            submitButton
        });
    }

    ftxui::Component LoginScene::component() {
        using namespace ftxui;

        return Renderer(container, [this] {
            return vbox ({
                text("T T R P G") | bold | center,
                separator(),
                text("Welcome to the TTRPG client") | center,
                separator(),
                hbox({
                    text("Username: "),
                    usernameInput->Render()
                }),
                separator(),
                submitButton->Render()
            }) | border | center;
        });

        /*
        auto screen = ScreenInteractive::Fullscreen();

        auto submit = CatchEvent(component, [&](Event event) {
            if (event == Event::Return) {
                screen.ExitLoopClosure()();
                return true;
            }

            return false;
        });

        screen.Loop(submit);

        return input;
        */
    }
}