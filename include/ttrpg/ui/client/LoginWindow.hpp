#pragma once

#include <QDialog>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT
public:
    explicit LoginWindow(QWidget* parent = nullptr);
    ~LoginWindow();
signals:
    void loginRequest(const QString& username);
private slots:
    void on_btnEnter_pressed();
    void toggleEnterEnabled();
private:
    Ui::LoginWindow* ui;
};

