#include <QApplication>
#include "ttrpg/application/ClientApplication.hpp"

int main(int argc, char* argv[]) {
    QApplication qtapp(argc, argv);

    ttrpg::application::ClientApplication app;
    app.run();

    return qtapp.exec();
}