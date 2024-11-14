#ifndef USER_H
#define USER_H

#include <QString>
#include <QObject>
#include <QtWidgets>
#include <QTcpSocket>
#include <vector>
#include <list>
#include "deck.h"

using namespace std;



class User:public QWidget
{
    Q_OBJECT
public:
    User();
    explicit User(QString nameParam,QString userNameParam,QString phoneNumberParam,QString addressParam,QString passwordParam,int idParam,QWidget* parent=nullptr);
    void setPassword(QString passwordParam);
    void setCoin(int coinParam);
    void addCards();
    static QString IPforClient;
    static int round;
    static QVector<User*> listOfUsers;
    static QVector<QVector<QString>> vec;  // for all cards :fisrt vector for name of card and inside one for power or number of card and It's initialize in addCards
    void send_message_start(QString data);
    QVector<QString> current_hand;
    static int won_person;
    static int randomCard;
    static int countForGameRun;
    static int sumOfWinRound[2];
    static int countOfWinUser[2];
    QTcpSocket* channel;
    int id;
    int winPredict;
    QString getUserName() const;
    void setUserName(const QString &value);

signals:


public slots:

    void send_message(QString);
    void send_message_for_round(QString);
    void notif_recieved();
    void connecttoserver();
    void Message(QString msg);


private:
    QString name;
    QString userName;
    QString address;
    QString password;
    int coin;
    QString phoneNumber;

    QVector<QString> vecTmp;
    QVector<QVector<QString>> cards; // first vector for number of players and second for cards of player | index 0 = player1 |index 1 = player2 ...
};



#endif
