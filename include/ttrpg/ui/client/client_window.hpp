#pragma once

#include <QMainWindow>
#include <QObject>

class ClientWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ClientWindow(QWidget *parent = nullptr);

signals:
};
