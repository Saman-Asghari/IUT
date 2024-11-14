#include "chooseclient.h"
#include "ui_chooseclient.h"
#include "login.h"

QString ChooseClient::usernameChooseClient = "";

ChooseClient::ChooseClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseClient)
{
    ui->setupUi(this);
}

ChooseClient::~ChooseClient()
{
    delete ui;
}

void ChooseClient::on_ok_clicked()
{
    string username;
    string name;
    string phoneNumber;
    string pass;
    string address;
    string tmp;

    ifstream file("Register.txt",ios::in);

    getline(file,name); // save name
    while(!file.eof()){
        getline(file,username);
        if(username == usernameChooseClient.toStdString()){
            getline(file,phoneNumber);
            getline(file,pass);
            getline(file,address);
            // call constructor of user(client)
            QString name2 = QString::fromStdString(name);
            QString phonenumber2 = QString::fromStdString(phoneNumber);
            QString pass2 = QString::fromStdString(pass);
            QString address2 = QString::fromStdString(address);
            User::IPforClient = ui->ip->text();
            User* x=new User(name2,usernameChooseClient,phonenumber2,address2,pass2,1);
            User* test = new User();
            test->listOfUsers.push_back(x);
            x->connecttoserver();
            this->hide();
        }
        else{
            // three getline for go to search another user
            getline(file,tmp);
            getline(file,tmp);
            getline(file,tmp);
            getline(file,name);
        }

    }
    file.close();
//    Login* l = new Login();
//    l->show();
}


void ChooseClient::on_cancel_clicked()
{
    this->close();
}

