#include "loginafterregister.h"
#include "ui_loginafterregister.h"
#include "login.h"
#include "serverorclient.h"




LoginAfterRegister::LoginAfterRegister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginAfterRegister)
{
    ui->setupUi(this);
}

LoginAfterRegister::~LoginAfterRegister()
{
    delete ui;
}

void LoginAfterRegister::on_login_clicked()
{
    QString userName = ui->username->text();
    QString pass = ui->password->text();

    ifstream file("Register.txt",ios::in);
    string line;
    bool checkUserName = false;
    bool checkPass = false;

    while (!file.eof()) {
        getline(file,line);
        if(line == userName.toStdString()){
            checkUserName = true;
            // initialize for choose client
            qDebug() << "login  :  " << QString::fromStdString(line);
            ChooseClient::usernameChooseClient = QString::fromStdString(line);
            ChooseServer::usernameChooseServer = QString::fromStdString(line);
            getline(file,line);
            getline(file,line);
            if(line == pass.toStdString()){
                // succecfully login...  so now choose server or client
                checkPass = true;
                this->hide();
                ServerOrClient* soc = new ServerOrClient();
                soc->show();
                break;
            }
        }
    }

    if(checkUserName == false){
        this->hide();
        QMessageBox::critical(this,"!!!","username was wrong");
        Login* l = new Login();
        l->show();

    }
    else if(checkPass == false){
        this->hide();
        QMessageBox::critical(this,"!!!","password was wrong");
        Login* l = new Login();
        l->show();
    }

    file.close();
}

