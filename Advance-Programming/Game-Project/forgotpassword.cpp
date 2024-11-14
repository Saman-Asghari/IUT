#include "forgotpassword.h"
#include "ui_forgotpassword.h"
#include "login.h"
#include <vector>
#include <fstream>
#include <QMessageBox>

using namespace std;

ForgotPassword::ForgotPassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForgotPassword)
{
    ui->setupUi(this);
}

ForgotPassword::~ForgotPassword()
{
    delete ui;
}

void ForgotPassword::on_OK_clicked()
{

    vector<QString> vec;
    string line;
    int c = 0;
    // read from file and change password
    ifstream file("Register.txt",ios::in);


    while(!file.eof()){
        getline(file,line);
        if(line == ui->lineEdit->text().toStdString()){
            vec.push_back(QString::fromStdString(line));
            getline(file,line);
            line = ui->lineEdit_2->text().toStdString();
            c++;
        }
        vec.push_back(QString::fromStdString(line));
    }

    file.close();

    if(c == 0){
        QMessageBox::critical(this,"fail","phone number not found");
        return;
    }

    // write updated content of file
    ofstream file2("Register.txt",ios::out);

    for(int i=0;i<vec.size();i++){
        file2 << vec.at(i).toStdString() << "\n";
    }

    file2.close();

    QMessageBox::information(this,"forgot password","change was succesfully");

    this->hide();
    Login* l = new Login();
    l->show();

}

