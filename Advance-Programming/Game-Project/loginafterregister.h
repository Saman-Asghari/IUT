#ifndef LOGINAFTERREGISTER_H
#define LOGINAFTERREGISTER_H

#include <QWidget>
#include <iostream>
#include <fstream>
#include <QMessageBox>
#include "chooseclient.h"
#include "chooseserver.h"

using namespace std;

namespace Ui {
class LoginAfterRegister;
}

class LoginAfterRegister : public QWidget
{
    Q_OBJECT

public:
    explicit LoginAfterRegister(QWidget *parent = nullptr);
    ~LoginAfterRegister();

private slots:
    void on_login_clicked();

private:
    Ui::LoginAfterRegister *ui;
};

#endif // LOGINAFTERREGISTER_H
