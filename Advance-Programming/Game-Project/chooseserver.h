#ifndef CHOOSESERVER_H
#define CHOOSESERVER_H

#include <QWidget>
#include <iostream>
#include <fstream>
#include "user.h"

namespace Ui {
class ChooseServer;
}

class ChooseServer : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseServer(QWidget *parent = nullptr);
    ~ChooseServer();
    static QString usernameChooseServer;


private slots:
    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::ChooseServer *ui;
};

#endif // CHOOSESERVER_H
