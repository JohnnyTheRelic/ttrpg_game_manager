#include <QDebug>
#include <QRegularExpressionValidator>

#include "ttrpg/ui/client/LoginWindow.hpp"
#include "ui_LoginWindow.h"

LoginWindow::LoginWindow(QWidget* parent) : QDialog(parent), ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setWindowTitle("Login");

    auto* validator = new QRegularExpressionValidator(QRegularExpression("[^\\s]*"), this);

    connect(ui->lineUserInput, &QLineEdit::textEdited, this, &LoginWindow::toggleEnterEnabled);

    ui->lineUserInput->setValidator(validator);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_btnEnter_pressed() {
    QString username = ui->lineUserInput->text();

    if(username.size() > 32 || username.size() < 3) {
        ui->lblError->setText("Username must be between 3 and 32 characters.");
        return;
    }

    ui->lineUserInput->clear();

    emit loginRequest(username);
    close();
}

void LoginWindow::toggleEnterEnabled() {
    if(ui->lineUserInput->text().isEmpty()) {
        ui->btnEnter->setEnabled(false);
    }
    else {
        ui->btnEnter->setEnabled(true);
    }
}
