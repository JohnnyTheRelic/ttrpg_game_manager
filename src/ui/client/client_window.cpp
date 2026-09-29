#include "ttrpg/ui/client/client_window.hpp"
#include "QLabel"

ClientWindow::ClientWindow(QWidget *parent)
    : QMainWindow{parent}
{
    setWindowTitle("TTRPG Client");
    resize(800, 600);

    auto* label = new QLabel("Welcome to the TTRPG client", this);
    label->setAlignment(Qt::AlignCenter);

    setCentralWidget(label);
}
