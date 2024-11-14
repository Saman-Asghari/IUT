#include "user.h"
#include "server.h"
#include "mainwindow.h"

QString User::IPforClient = "";
int User::round = 0;
QVector<User*> User::listOfUsers;
QVector<QVector<QString>> User::vec;
int User::won_person;
int User::randomCard = 0;
int User::countForGameRun = 0;
int User::sumOfWinRound[2] = {0,0};
int User::countOfWinUser[2] = {0,0};  // jam emtiaz haye kol


User::User(){

}

User::User(QString nameParam, QString userNameParam, QString phoneNumberParam, QString addressParam, QString passwordParam,int idParam,QWidget *parent): QWidget(parent)
{
    name = nameParam;
    userName = userNameParam;
    phoneNumber = phoneNumberParam;
    password = passwordParam;
    address = addressParam;
    id = idParam;
//    MainWindow* mm = new MainWindow(this);
//    mm->hide();

}

void User::setCoin(int coinParam){
    int coinTmp = this->coin;
    coinTmp += coinParam;
    coin = coinTmp;
}

void User::connecttoserver()
{
    channel = new QTcpSocket(this);
    channel->connectToHost(IPforClient,5000);
    if(channel->waitForConnected(3000))
        {
           // Message("connected with socket to server");
            connect(channel,&QTcpSocket::readyRead,this,&User::notif_recieved);
        }
        else
        {
            Message("could not connect to server");
        }

}
void User::Message(QString msg)
{
    QMessageBox::information(this,"!!!",msg);
}

QString User::getUserName() const
{
    return userName;
}

void User::setUserName(const QString &value)
{
    userName = value;
}
void User::send_message(QString msg)
{
    QString tmp = "card " + msg;
    QString message = tmp; //the struct we are gonna send to server
    channel->write(message.toUtf8());

}

void User::send_message_for_round(QString msg)
{
    channel->write(msg.toUtf8());
}

void User::send_message_start(QString data){  // just for give "start the main game" and start round 1
    channel->write(data.toUtf8());
}

void User::addCards(){
    // ew are adding all cards then we choose random cards from this vector

    for(int i=1;i<9;i++){ // adding toti cards
        QString j = QString::number(i);
        vecTmp.push_back("toti.png"+j);
    }
    vec.push_back(vecTmp);
    vecTmp.clear();
    for(int i=1;i<9;i++){ // adding ganj cards
        QString j = QString::number(i);
        vecTmp.push_back("ganj44.png"+j);
    }
    vec.push_back(vecTmp);
    vecTmp.clear();

    for(int i=1;i<9;i++){ // adding naghshe cards
        QString j = QString::number(i);
        vecTmp.push_back("naghshe44.png"+j);
    }
    vec.push_back(vecTmp);
    vecTmp.clear();

    for(int i=1;i<9;i++){ // adding parcham-dozd-daryayi cards
        QString j = QString::number(i);
        vecTmp.push_back("parcham-dozd-daryayi44.png"+j);
    }
    vec.push_back(vecTmp);
    vecTmp.clear();

    for(int i=1;i<5;i++){ // dozd-daryayi cards
        QString j = QString::number(i);
        vecTmp.push_back("dozd-daryayi.png"+j);
    }
    vec.push_back(vecTmp);
    vecTmp.clear();

    for(int i=1;i<4;i++){ // malake cards
        QString j = QString::number(i);
        vecTmp.push_back("malake44.png"+j);
    }
    vec.push_back(vecTmp);
    vecTmp.clear();

    for(int i=1;i<4;i++){ // jomjome cards
        QString j = QString::number(i);
        vecTmp.push_back("padeshah-jojome44.png"+j);
    }
    vec.push_back(vecTmp);
    vecTmp.clear();
}

void User::notif_recieved()
{
    QByteArray notif_msg = channel->readAll(); //the struct we are gonna reicive when the server tsend the winner of the round
    QString DataAsString = QString(notif_msg);
    string dataasstringtmp=DataAsString.toStdString();
    qDebug() << "msgggg : " <<  DataAsString;

    if(DataAsString.contains("round")){  // DataAsString.contains("png")
        MainWindow* mm = new MainWindow(this);
        MainWindow::listOfWindow.push_back(mm);
        if(DataAsString.contains("round")){
            if(randomCard == 0){
                qDebug() << "randommm";
                QTimer::singleShot(1000, [=]() {
                    mm->setplayersrandomcard(vec);
                });
            }
            User::randomCard++;
            QTimer::singleShot(2000, [=]() {
                qDebug() << "showwwww";
                mm->showBoardGame();
            });
        }

    }

    else if(DataAsString.contains("png")){
        QTimer::singleShot(2000, [=]() {
            //mm->showBoardGame();
            MainWindow::listOfWindow[this->id]->reciveCard(DataAsString);
        });
        qDebug() << "pngpngpngpgnpgn";
    }

    else if(DataAsString.contains("start")){ // choose who start first
        User::round++;
        addCards();
        char n1tmp=dataasstringtmp[6];
        int n1=n1tmp - '0';
        char n2tmp=dataasstringtmp[7];
        int n2=n2tmp - '0';
        MainWindow* m = new MainWindow(this);
        QTimer::singleShot(1000, [=]() {
            m->startTheGameByToti(n1,n2);
        });
    }
    else{   // convert to struct
        qDebug() << "structttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt";

//        QChar winnerFromServer = dataasstringtmp[13];
//        int winnerFromServerInt = winnerFromServer.digitValue();

//        User::sumOfWinRound[winnerFromServerInt]++;


//        QByteArray data = channel->readAll();
//        Cards receivedStruct;
//        memcpy(&receivedStruct, data.constData(), sizeof(Cards));
//        int number = receivedStruct.number;
//        int power = receivedStruct.power;
//        QString name = receivedStruct.name;
    }
}
