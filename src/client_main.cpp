#include <QApplication>
#include "ttrpg/ui/client/LoginWindow.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    LoginWindow window;
    window.show();

    return app.exec();
}