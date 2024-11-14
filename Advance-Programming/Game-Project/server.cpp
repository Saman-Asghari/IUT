#include "server.h"
#include <QRandomGenerator>
#include "mainwindow.h"


QString Server::IP = "";
int Server::roundFromServer = 0;
int Server::cardPlay = 0;
int Server::checkForServer = 0;
int Server::winner = 0;

Server::Server(int cap,QWidget *parent) : QWidget(parent)
{
    capacity=cap;
    m_server = new QTcpServer(this);
    connect(m_server,&QTcpServer::newConnection,this,&Server::request_for_connection);
    if(!m_server->listen(QHostAddress(IP),5000))
        {
            Message("can not connect the server on this port");
        }
        else
        {
            m_port = m_server->serverPort();
            Message("server created");
        }

}
Server::~Server()
{
//    Message("destroyed");
//    if(m_server->isListening())
//    {
//        m_server->close();
//        foreach(QTcpSocket* channel,socket_list)
//        {
//            delete channel;
//        }
//    }
}

void Server::request_for_connection()
{
    QTcpSocket* channel = m_server->nextPendingConnection();

    if(channel == nullptr)
    {
        Message("can not create a new connection with socket");
        return;
    }
    else{
        if(socket_list.size()==capacity){
            Message("server is full");
            channel->disconnect();
            return;
        }

        else{
            int i=socket_list.size()+1;
            QString m=QString::number(i);
            Message("connected the socket"+m);
            socket_list.append(channel);
            connect(channel,&QTcpSocket::readyRead,this,&Server::recieved_message);
            if(socket_list.size()==capacity){
                startgame();
            }
        }
    }
}

QByteArray Server::recieved_message()
{
    QByteArray x=qobject_cast<QTcpSocket*>(sender())->readAll();
    QString xTmp(x);
    qDebug() << "serverrrrrrrrrr :   " << xTmp;

    if(x == "end round"){
        for(QTcpSocket *client :socket_list ) {
            client->write("round");
        }
    }
    else if(x == "change cards"){
        int random1 = QRandomGenerator::global()->bounded(User::listOfUsers[0]->current_hand.size());
        int random2 = QRandomGenerator::global()->bounded(User::listOfUsers[1]->current_hand.size());

        QString p1 = User::listOfUsers[0]->current_hand.at(random1);
        QString p2 = User::listOfUsers[1]->current_hand.at(random2);
        qDebug() << "User::listOfUsers[0]->current_hand.at(random1) : " << User::listOfUsers[0]->current_hand.at(random1);
        qDebug() << "User::listOfUsers[1]->current_hand.at(random2) : " << User::listOfUsers[1]->current_hand.at(random2);

        QString tmp = p1;
        p1 = p2;
        p2 = tmp;


        User::listOfUsers[0]->current_hand.replace(random1,p1);
        User::listOfUsers[1]->current_hand.replace(random2,p2);

        qDebug() << "User::listOfUsers[0]->current_hand.at(random1) : " << User::listOfUsers[0]->current_hand.at(random1);
        qDebug() << "User::listOfUsers[1]->current_hand.at(random2) : " << User::listOfUsers[1]->current_hand.at(random2);


    }
    else{
        for(QTcpSocket *client :socket_list ) {
            client->write(x);
        }
        if(xTmp.contains("png")){
            Server::cardPlay++;
            saveCards.push_back(xTmp);
            if(saveCards.size() == 2){
                chooseWinner();
                saveCards.clear();
            }
        }
    }
    return x;
}

bool Server::isListening()
{
    return m_server->isListening();
}

int Server::get_capacity()
{
    return capacity;
}


void Server::chooseWinner()
{

    QString name;
    int power,id;
    Cards x,y;

    for(int i=0;i<saveCards.size();i++){
        QString tmp = saveCards.at(i);
        for(int j=0;j<tmp.size() - 6;j++){
            name += tmp[j];
        }
        power = tmp[tmp.size() - 2].digitValue();
        id = tmp[tmp.size() - 1].digitValue();
        qDebug() << "name : " << name;
        qDebug() << "power : " << power;
        qDebug() << "id : " << id;
        if(i == 0){
            x.name = name;
            x.power = power;
            x.id = id;
        }
        else if(i == 1){
            y.name = name;
            y.power = power;
            y.id = id;
        }
        name = "";
    }
    // mantegh

    int winner;

    if(x.name==y.name){
        if(x.power>y.power){
            winner=x.id;
        }
        else{
            winner =y.id;
        }
    }
     else{
       if(x.name.contains("ganj")||x.name.contains("toti") ||x.name.contains("naghshe")){
         if(y.name.contains("parcham") ||y.name.contains("padeshah-jojome") ||y.name.contains("malake") ||y.name.contains("dozd-daryayi")){
             winner=y.id;
         }
         else{
             //winner=winner(ghabli);//haman nafar ghabli barande ast dar asl engar bazikon rad dade ast
             winner = x.id;
         }
       }
       if(x.name.contains("parcham")){
               if(y.name.contains("padeshah-jojome") ||y.name.contains("malake") ||y.name.contains("dozd-daryayi")){
                   winner=y.id;
               }
               else{
                   winner=x.id;
               }
            }
        if(x.name.contains("padeshah-jojome")){
            if(y.name.contains("malake")){
                winner=y.id;
            }
            else{
                winner=x.id;
            }
            }
        if(x.name.contains("malake")){
            if(y.name.contains("dozd-daryayi")){
                winner=y.id;
            }
            else{
                winner=x.id;
            }
         }


        if(x.name.contains("dozd-daryayi")){
                if(y.name.contains("padeshah")){
                    winner=y.id;
                }
                else{
                    winner=x.id;
                }
            }
    }
    qDebug() << "Winerrrrrrrrrrrrrrrrrr : " << winner;
    QString winnerString = QString::number(winner);
    qDebug() << "winnerString winnerString winnerString winnerString : " << winnerString;

    QString winnerFromServer = winnerString;
    int winnerFromServerInt = winnerFromServer.toInt();

     qDebug() << "winnerFromServer : " << winnerString;
    User::countOfWinUser[winnerFromServerInt]++;
    qDebug() << "User::countOfWinUser[winnerFromServerInt]   " << User::countOfWinUser[winnerFromServerInt];

    if(winnerString.contains("malake")){
        User::sumOfWinRound[winnerFromServerInt] += 20;
    }
    else if(winnerString.contains("padeshah-jojome")){
        User::sumOfWinRound[winnerFromServerInt] += 15;
    }
    else if(winnerString.contains("dozd-daryayi")){
        User::sumOfWinRound[winnerFromServerInt] += 10;
    }
    else{
        User::sumOfWinRound[winnerFromServerInt]++;
    }

    if(cardPlay == User::round * 2){
        MainWindow::listOfWindow[0]->hide();
        MainWindow::listOfWindow[1]->hide();
        MainWindow::check = 0;
        User::randomCard = 0;
        User::round += 2;
        int winUser = User::listOfUsers[0]->sumOfWinRound[0];
        QString winUserString = QString::number(winUser);
        QString winWindow = MainWindow::listOfWindow[0]->reciveWin();
        int winUser2 = User::listOfUsers[1]->sumOfWinRound[1];
        QString winUserString2 = QString::number(winUser2);
        QString winWindow2 = MainWindow::listOfWindow[1]->reciveWin();
        if(User::countOfWinUser[0] == winWindow.toInt()){
            if(winWindow.toInt() == 0){
                winUser += 10 * (User::round/2);
                User::listOfUsers[0]->sumOfWinRound[0] = winUser;
                qDebug() << "player 11111111111111111111111111  win";
                winUser2 -= 10 * (User::round/2);
                User::listOfUsers[1]->sumOfWinRound[1] = winUser2;
            }
            else{
                winUser += 10 * User::countOfWinUser[0];
                User::listOfUsers[0]->sumOfWinRound[0] = winUser;
                qDebug() << "player 11111111111111111111111111  win";
                winUser2 -= 10 * User::countOfWinUser[1];
                User::listOfUsers[1]->sumOfWinRound[1] = winUser2;
            }
        }
        else if(User::countOfWinUser[1] == winWindow2.toInt()){
            if(winWindow2.toInt() == 0){
                winUser2 += 10 * (User::round / 2);
                User::listOfUsers[1]->sumOfWinRound[1] = winUser2;
                qDebug() << "player 2222222222222222222222222 win";
                winUser -= 10 * (User::round / 2);
                User::listOfUsers[0]->sumOfWinRound[0] = winUser;
            }
            else{
                winUser2 += 10 * User::countOfWinUser[1];
                User::listOfUsers[1]->sumOfWinRound[1] = winUser2;
                qDebug() << "player 2222222222222222222222222 win";
                winUser -= 10 * User::countOfWinUser[0];
                User::listOfUsers[0]->sumOfWinRound[0] = winUser;
            }
        }
        else{
            winUser -= 10 * User::countOfWinUser[0];
            User::listOfUsers[0]->sumOfWinRound[0] = winUser;

            winUser2 -= 10 * User::countOfWinUser[1];
            User::listOfUsers[1]->sumOfWinRound[1] = winUser2;
            qDebug() << "no body winnnnnnnnnnnnnnnnnnnnnnnn";
        }
        if(User::round == 10){ // end of game
            if(User::sumOfWinRound[0] > User::sumOfWinRound[1]){
                qDebug() << "player 111111111111111111111111  win";
                QMessageBox::information(this,"winner",User::listOfUsers[0]->getUserName() + " win the game");
            }
            else{
                QMessageBox::information(this,"winner",User::listOfUsers[1]->getUserName() + " win the game");
                qDebug() << "player 222222222222222222222222  win";
            }
        }
        Server::cardPlay = 0;
        MainWindow::listOfWindow.clear();
            Server::checkForServer++;
            foreach(QTcpSocket* client,socket_list){
                client->write("round");
            }
        qDebug() << "if forrrrr toundddd";
    }


//    if(Server::checkForServer == 0){
//        foreach(QTcpSocket* client,socket_list){
//            client->write(winnerString.toUtf8());
//        }
//    }
    Server::checkForServer = 0;

}

void Server::self_destruction()
{
    //Message("destruction is called");
    deleteLater();
}

void Server::startgame()
{
    int player1 = QRandomGenerator::global()->bounded(1, 9);
    int player2 = QRandomGenerator::global()->bounded(1, 9);
    while(player2 == player1){
        player2 = QRandomGenerator::global()->bounded(1, 9);
    }
    QString p1=QString::number(player1);
    QString p2=QString::number(player2);
    QString rsult=p1+p2;
    QString x="start "+rsult;

    QByteArray temp=x.toUtf8();
    for(QTcpSocket *client :socket_list ) {
        client->write(temp);
    }

}

void Server::startGameByMsg(){
    QString x = "round";
    QByteArray tmp=x.toUtf8();
    for(QTcpSocket *client :socket_list ) {
        client->write(tmp);
    }
}

quint16 Server::port() const
{
    return m_port;
}

void Server::Message(QString msg)
{
    QMessageBox::information(this,"!!!",msg);
}
