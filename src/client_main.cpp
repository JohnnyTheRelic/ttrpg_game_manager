#include <QApplication>
#include "ttrpg/ui/client/client_window.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    ClientWindow window;
    window.show();

    return app.exec();
}