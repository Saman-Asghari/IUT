#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QTcpSocket>
#include "user.h"

using namespace std;



class Server : public QWidget
{
    Q_OBJECT
   public:
       explicit Server(int cap,QWidget *parent = nullptr);
        Server(){
        };
       ~Server();

       void request_for_connection();
       QByteArray recieved_message();
       bool isListening();
       int get_capacity();
       void chooseWinner();
       static QString IP;
       static int roundFromServer;
       static int cardPlay;
       static int checkForServer;
       static int winner;
       quint16 port() const;

   signals:

   public slots:
       void self_destruction();
       void startgame();
       void startGameByMsg();


   private:

       struct Cards{
           int id;
           int power;
           QString name;
       };

       QTcpServer* m_server;
       QPlainTextEdit* msg_box;
       QVBoxLayout* layout;
       QList<QTcpSocket*> socket_list;
       quint16 m_port;
       int capacity;
       void Message(QString msg);
       vector<QString> saveCards;
};

#endif // SERVER_H
