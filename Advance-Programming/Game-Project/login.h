#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_Register_clicked();

    void on_forgotPass_clicked();



    void on_login_clicked();

    void on_changeInformation_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
