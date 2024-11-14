#include "changeinformation.h"
#include "ui_changeinformation.h"
#include "login.h"

ChangeInformation::ChangeInformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangeInformation)
{
    ui->setupUi(this);
}

ChangeInformation::~ChangeInformation()
{
    delete ui;
}

void ChangeInformation::on_ok_clicked()
{
     string line;

     ifstream file("Register.txt",ios::in);
     vector<QString> vec;
     bool check = false;

     while(!file.eof()){
        getline(file,line);
        if(QString::fromStdString(line) == ui->prename->text()){
            check = true;

            vec.push_back(ui->newname->text());
            vec.push_back(ui->newusername->text());
            vec.push_back(ui->nrephonenumber->text());
            vec.push_back(ui->newpassword->text());
            vec.push_back(ui->newaddress->toPlainText());
            // for save another user ...
            getline(file,line);
            getline(file,line);
            getline(file,line);
            getline(file,line);
            getline(file,line);
        }
        vec.push_back(QString::fromStdString(line));
     }

     if(check = false){
         QMessageBox::critical(this,"fail","information was wrong");
     }
     file.close();

     // update file
     ofstream file2("Register.txt",ios::out);
     for(int i=0;i<vec.size();i++){
         file2 << vec.at(i).toStdString() << "\n";
     }
     file2.close();

     this->close();
     Login* l = new Login();
     l->show();

}


void ChangeInformation::on_cancel_clicked()
{
    this->close();
    Login* l = new Login();
    l->show();
}

