#include "login.h"
#include "ui_login.h"
#include "register.h"
#include "forgotpassword.h"
#include "loginafterregister.h"
#include "changeinformation.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

}

Login::~Login()
{
    delete ui;
}

void Login::on_Register_clicked()
{
    Register* r = new Register();
    this->hide();
    r->show();
}


void Login::on_forgotPass_clicked()
{
    this->hide();
    ForgotPassword* fp = new ForgotPassword();
    fp->show();
}


void Login::on_login_clicked()
{
    this->hide();
    LoginAfterRegister* laf = new LoginAfterRegister();
    laf->show();
}


void Login::on_changeInformation_clicked()
{
    this->hide();
    ChangeInformation* chinf = new ChangeInformation();
    chinf->show();
}

