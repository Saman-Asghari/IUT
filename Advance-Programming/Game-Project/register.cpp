#include "register.h"
#include "ui_register.h"
#include "user.h"
#include "mainwindow.h"
#include "login.h"
#include <QMessageBox>
#include <QFileInfo>
#include <fstream>
#include <QDir>

using namespace std;

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_ok_clicked()
{
    QString name = ui->name->text();
    QString userName = ui->userName->text();
    QString password = ui->password->text();
    QString phoneNumber = ui->phoneNumber->text();
    QString address = ui->address->toPlainText();

    //User(name,userName,phoneNumber,address,password);

    // save into file
    ofstream file("Register.txt",ios::app);

    file << name.toStdString() << "\n";
    file << userName.toStdString() << "\n";
    file << phoneNumber.toStdString() << "\n";
    file << password.toStdString() << "\n";
    file << address.toStdString() << "\n";

    file.close();

    QMessageBox::information(this,"Register","succesfully Register");

    this->hide();
    Login* l = new Login();
    l->show();

}

