#include "chooseserver.h"
#include "ui_chooseserver.h"
#include "server.h"
#include "login.h"

QString ChooseServer::usernameChooseServer = "";

ChooseServer::ChooseServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseServer)
{
    ui->setupUi(this);
}

ChooseServer::~ChooseServer()
{
    delete ui;
}

void ChooseServer::on_ok_clicked()
{
    Server::IP = ui->ip->text();
    // call server

    Server* x=new Server(2);
    this->hide();

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
        if(username == usernameChooseServer.toStdString()){
            getline(file,phoneNumber);
            getline(file,pass);
            getline(file,address);
            // call constructor of user(client)
            QString name2 = QString::fromStdString(name);
            QString phonenumber2 = QString::fromStdString(phoneNumber);
            QString pass2 = QString::fromStdString(pass);
            QString address2 = QString::fromStdString(address);
            User::IPforClient = ui->ip->text();
            User* xz=new User(name2,ChooseServer::usernameChooseServer,phonenumber2,address2,pass2,0);
            User* test = new User();
//            User* a = new User("ali","mamad","11222","address2","1234");
//            a->connecttoserver();
            test->User::listOfUsers.push_back(xz);
            xz->connecttoserver();
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

   Login* l = new Login();
    l->show();
}


void ChooseServer::on_cancel_clicked()
{
    this->close();
}

