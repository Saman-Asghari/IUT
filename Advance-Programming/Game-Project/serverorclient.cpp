#include "serverorclient.h"
#include "ui_serverorclient.h"
#include "chooseserver.h"
#include "chooseclient.h"

ServerOrClient::ServerOrClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerOrClient)
{
    ui->setupUi(this);
}

ServerOrClient::~ServerOrClient()
{
    delete ui;
}

void ServerOrClient::on_server_clicked()
{
    this->hide();
    ChooseServer* chs = new ChooseServer();
    chs->show();
}

void ServerOrClient::on_client_clicked()
{
    this->hide();
    ChooseClient* chc = new ChooseClient();
    chc->show();
}

