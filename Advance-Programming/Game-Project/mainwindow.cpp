#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "server.h"
#include <QRandomGenerator>
#include <QIcon>

int MainWindow::countForCard = 0;
int MainWindow::check = 0;
QVector<MainWindow*> MainWindow::listOfWindow;
int MainWindow::sendClientForChooseWin = 0;
bool isLocked = false;


MainWindow::MainWindow(User*x,QWidget *parent) : QMainWindow(parent){
    temp=x;
//    connect(temp->channel,&QTcpSocket::readyRead,this,&MainWindow::farz);


//    setStyleSheet("background-image: url(:/res/zamin-bazi-44.png);background-repeat: no-repeat; background-position: center;background-size: cover;");
//    QWidget *centralWidget = new QWidget(this);
//    setCentralWidget(centralWidget);

//    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

//    QGridLayout *layout = new QGridLayout();
//    mainLayout->addLayout(layout);

    // set cards
//    CardWidget *card1 = new CardWidget(":/res/toti.png",this);
//    layout->addWidget(card1, 0, 0);
//    CardWidget *card2 = new CardWidget(":/res/toti.png",this);
//    layout->addWidget(card2, 1, 0);
//    CardWidget *card3 = new CardWidget(":/res/toti.png",this);
//    layout->addWidget(card3, 2, 0);
//    CardWidget *card4 = new CardWidget(":/res/toti.png",this);
//    layout->addWidget(card4, 3, 0);
//    CardWidget *card5 = new CardWidget(":/res/toti.png",this);
//    layout->addWidget(card5, 4, 0);
//    CardWidget *card6 = new CardWidget(":/res/toti.png",this);
//    layout->addWidget(card6, 5, 0);
//    CardWidget *card7 = new CardWidget(":/res/toti.png",this);
//    layout->addWidget(card7, 6, 0);
//    CardWidget *card8 = new CardWidget(":/res/toti.png",this);
//    layout->addWidget(card8, 7, 0);
//    CardWidget *card9 = new CardWidget(":/res/toti.png",this);
//    layout->addWidget(card9, 8, 0);
//    CardWidget *card10 = new CardWidget(":/res/toti.png",this);
//    layout->addWidget(card10, 9, 0);
//    CardWidget *card11 = new CardWidget(":/res/toti.png",this);
//    layout->addWidget(card11, 10, 0);
//    CardWidget *card12 = new CardWidget(":/res/toti.png",this);
//    layout->addWidget(card12, 11, 0);
//    CardWidget *card13 = new CardWidget(":/res/toti.png",this);
//    layout->addWidget(card13, 12, 0);
//    CardWidget *card14 = new CardWidget(":/res/toti.png",this);
//    layout->addWidget(card14, 13, 0);

//    layout->setContentsMargins(70, 50, 50, 50);

//    QGridLayout *layout2 = new QGridLayout();
//    mainLayout->addLayout(layout2);

//    // set cards for another player
//    CardWidget *card1b = new CardWidget(":/res/dozd-daryayi",this);
//    layout2->addWidget(card1b, 1, 8);
//    CardWidget *card2b = new CardWidget(":/res/dozd-daryayi",this);
//    layout2->addWidget(card2b, 2, 8);
//    CardWidget *card3b = new CardWidget(":/res/dozd-daryayi",this);
//    layout2->addWidget(card3b, 3, 8);
//    CardWidget *card4b = new CardWidget(":/res/dozd-daryayi",this);
//    layout2->addWidget(card4b, 4, 8);
//    CardWidget *card5b = new CardWidget(":/res/dozd-daryayi",this);
//    layout2->addWidget(card5b, 5, 8);
//    CardWidget *card6b = new CardWidget(":/res/dozd-daryayi",this);
//    layout2->addWidget(card6b, 6, 8);
//    CardWidget *card7b = new CardWidget(":/res/dozd-daryayi",this);
//    layout2->addWidget(card7b, 7, 8);
//    CardWidget *card8b = new CardWidget(":/res/dozd-daryayi",this);
//    layout2->addWidget(card8b, 8, 8);
//    CardWidget *card9b = new CardWidget(":/res/dozd-daryayi",this);
//    layout2->addWidget(card9b, 9, 8);
//    CardWidget *card10b = new CardWidget(":/res/dozd-daryayi",this);
//    layout2->addWidget(card10b, 10, 8);
//    CardWidget *card11b = new CardWidget(":/res/dozd-daryayi",this);
//    layout2->addWidget(card11b, 11, 8);
//    CardWidget *card12b = new CardWidget(":/res/dozd-daryayi",this);
//    layout2->addWidget(card12b, 12, 8);
//    CardWidget *card13b = new CardWidget(":/res/dozd-daryayi",this);
//    layout2->addWidget(card13b, 13, 8);
//    CardWidget *card14b = new CardWidget(":/res/dozd-daryayi",this);
//    layout2->addWidget(card14b, 14, 8);

//    layout2->setContentsMargins(900, 50, 50, 50);

    //setWindowTitle("Cards");
    //showFullScreen();
    //resize(1450,1000);
}

//void MainWindow::sendMsg(QString message)
//{
//    //emit sendMsg(message); // Emit the signal with the provided message
//}


void MainWindow::startTheGameByToti(int random1,int random2){
    setStyleSheet("background-image: url(:/res/zamin-bazi-44.png);background-repeat: no-repeat; background-position: center;background-size: cover;");
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);



    QString numberString;

    QGridLayout *layout = new QGridLayout();
    mainLayout->addLayout(layout);

    CardWidget *card1 = new CardWidget(":/res/toti.png",this);
    layout->addWidget(card1, 5, 2);
    numberString = QString::number(random1);
    QLabel *label1 = new QLabel(numberString, this);
    layout->addWidget(label1, 5, 3);
    layout->setContentsMargins(70, 50, 50, 50);

    QGridLayout *layout2 = new QGridLayout();
    mainLayout->addLayout(layout2);

    CardWidget *card2 = new CardWidget(":/res/toti-barax.png",this);
    layout2->addWidget(card2, 5, 2);
    numberString = QString::number(random2);
    QLabel *label2 = new QLabel(numberString, this);
    layout2->addWidget(label2,5,1);
    layout2->setContentsMargins(500, 50, 50, 50);

    QString choose;
    if(random1 > random2){
        choose = User::listOfUsers[0]->getUserName();
        temp->won_person=0;
    }
    else{
        choose = User::listOfUsers[1]->getUserName();
        temp->won_person=1;
    }

    resize(1450,1000);
    this->show();
    QMessageBox::information(this,"start",choose + " start first");
    this->hide();

    if(check == 0){
        temp->listOfUsers.at(0)->send_message_start("round"); // index 0 is server(admin client)
    }
    check++;

}

void MainWindow::setplayersrandomcard(QVector<QVector<QString>> x)
{
    source_cards=x;
    for(int k=0;k<2;k++){
        for(int i=0;i<User::round;i++){
            int jense=QRandomGenerator::global()->bounded(0,7);
            int number;
            if(jense>=0&&jense<=3){
                number=QRandomGenerator::global()->bounded(0,8);
                while(number == jense || source_cards[jense][number] == "0"){
                    number=QRandomGenerator::global()->bounded(0,8);
                }
            }
            if(jense==4){
                number=QRandomGenerator::global()->bounded(0,4);
                while(number == jense || source_cards[jense][number] == "0"){
                    number=QRandomGenerator::global()->bounded(0,4); // 8
                }
            }
            if(jense==5||jense==6){
                number=QRandomGenerator::global()->bounded(0,3);
                while(number == jense || source_cards[jense][number] == "0"){
                    number=QRandomGenerator::global()->bounded(0,3); // 8
                }
            }
            User::listOfUsers[k]->current_hand.push_back(source_cards[jense][number]);
            source_cards[jense][number] = "0";
        }
    }

}

void MainWindow::showBoardGame()
{
    QLabel* nameOfUser = new QLabel();
    nameOfUser->setText("player " + temp->getUserName());
    le = new QLineEdit();
    connect(le,&QLineEdit::textChanged,this,&MainWindow::reciveWin);


    setStyleSheet("background-image: url(:/res/zamin-bazi-44.png);background-repeat: no-repeat; background-position: center;background-size: cover;");

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget); // centralWidget

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    QGridLayout *layout = new QGridLayout();
    mainLayout->addLayout(layout);
//    QGridLayout *layout2 = new QGridLayout();
//    mainLayout->addLayout(layout2);

    int row = 0;
    QString tmp;

    for(int i=0;i<temp->current_hand.size();i++){
        int sizeInside = temp->current_hand[i].size();
        QString number = temp->current_hand[i][sizeInside - 1];

        for(int j=0;j<sizeInside - 1;j++){
            tmp += temp->current_hand[i][j];
        }
        qDebug() << "img : " << tmp;
        QString img = ":/res/"+tmp;
        //CardWidget *card = new CardWidget(img,this);
        QIcon icon(img);
        QPushButton* btn = new QPushButton(this);
        btn->setIcon(icon);
        btn->setIconSize(icon.actualSize(QSize(180, 70)));
        QString nn = QString::number(i);

        btn->setObjectName(nn);
        connect(btn,&QPushButton::clicked,this,&MainWindow::onClickButton);

        btn->setText(number);
        button.push_back(btn);

        layout->addWidget(btn, row, 4, 1, 2);
        layout->setAlignment(btn, Qt::AlignLeft);
        layout->setContentsMargins(70, 50, 50, 50);
        row++;

        tmp = "";
    }

    exit = new QPushButton("Exit", centralWidget);
    connect(exit,&QPushButton::clicked,this,&MainWindow::exitButton);

    changeCard = new QPushButton("change card",centralWidget);
    connect(changeCard,&QPushButton::clicked,this,&MainWindow::change);

    QPushButton* lockButton = new QPushButton("Lock", centralWidget);
    isLocked = false;
    QObject::connect(lockButton, &QPushButton::clicked, [this, lockButton,&isLocked]() {
        if (isLocked) {
            // Enable all widgets
            for(int j=0;j<2;j++){
                for(int i=0;i<button.size();i++){
                    listOfWindow[j]->button.at(i)->setEnabled(true);
                }
            }
            for(int j=0;j<2;j++){
                listOfWindow[j]->le->setEnabled(true);
                listOfWindow[j]->exit->setEnabled(true);
                listOfWindow[j]->changeCard->setEnabled(true);
            }
            lockButton->setText("Lock");
        } else {
            // Disable all widget
            for(int j=0;j<2;j++){
                for(int i=0;i<button.size();i++){
                    listOfWindow[j]->button.at(i)->setEnabled(false);
                }
            }
            for(int j=0;j<2;j++){
                listOfWindow[j]->le->setEnabled(false);
                listOfWindow[j]->exit->setEnabled(false);
                listOfWindow[j]->changeCard->setEnabled(false);
            }
            lockButton->setEnabled(true);
            lockButton->setText("Resume");
        }
        isLocked = !isLocked; // Toggle the lock state
    });




    mainLayout->addStretch();
    mainLayout->addWidget(lockButton);
    mainLayout->addWidget(changeCard);
    changeCard->move(4000,1000);
    mainLayout->addWidget(exit);
    exit->move(4000,900);
    nameOfUser->move(3000,2000);
    mainLayout->addWidget(le);
    le->move(4000,800);
    le->setFixedHeight(20);
    le->setFixedWidth(80);
    mainLayout->addWidget(nameOfUser);
    nameOfUser->move(4000,700);


    //le->setGeometry(300,700,20,20);

    //layout->addWidget(card, row, 2);
    //layout->addWidget(label, row, 3);



//    for(int k=0;k<2;k++){
//        for(int i=0;i<User::listOfUsers[k]->current_hand.size();i++){

//            int sizeInside = User::listOfUsers[k]->current_hand[i].size();
//            QString number = User::listOfUsers[k]->current_hand[i][sizeInside - 1];

//            for(int j=0;j<sizeInside - 1;j++){
//                tmp += User::listOfUsers[k]->current_hand[i][j];
//            }
//            QString img = ":/res/"+tmp;
//            CardWidget *card = new CardWidget(img,this);
//            QLabel *label = new QLabel(number, this);
//            QPushButton* btn = new QPushButton(this);
//            btn->setText("choose");
//            row++;
//            tmp = "";
//            if(k == 1){  // MainWindow::countForCard > 2*User::listOfUsers[k]->round
//                layout2->addWidget(card, row, 4);
//                layout2->addWidget(label, row, 3);
//                layout2->addWidget(btn,row,3/5);
//                layout2->setContentsMargins(500, 50, 50, 50);
//            }
//            else{
//                layout->addWidget(card, row, 2);
//                layout->addWidget(label, row, 3);
//                layout->addWidget(btn, row, 4, 1, 2); // 4
//                layout->setAlignment(btn, Qt::AlignLeft);
//                layout->setContentsMargins(70, 50, 50, 50);
//            }
//        }
//    }
//    mainLayout->addLayout(layout);
//    mainLayout->addLayout(layout2);

    resize(1450,1000);
    this->show();

//    if(User::countForGameRun == 0){
//        qDebug() << "if for game run ";
//        temp->send_message_for_round("game run");
//        QTimer::singleShot(1000, [=]() {
//           temp->send_message_for_round("game run");
//        });
//    }
    //    User::countForGameRun++;
}

void MainWindow::chooseWinner()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (isLocked) {
        event->ignore();
    } else {
        event->accept();
    }
}


int MainWindow::onClickButton()
{
    QPushButton* btn2 = qobject_cast<QPushButton*>(sender());
    int i = 0;
    for(i=0;i<button.size();i++){
        if(btn2 == button.at(i)){
            break;
        }
    }

    button.at(i)->hide();
    button.erase(button.begin() + i);

    //hideCards.push_back(temp->current_hand[i]);
    QString tmpCurrentHand = temp->current_hand[i];
    temp->current_hand.erase(temp->current_hand.begin() + i);
    QString ID = QString::number(temp->id);
    temp->send_message_for_round(tmpCurrentHand + ID);

//    if(User::listOfUsers[0]->current_hand.size() == 0 && User::listOfUsers[1]->current_hand.size() == 0){
//        listOfWindow[0]->hide();
//        listOfWindow[1]->hide();
//        MainWindow::check = 0;
//        User::randomCard = 0;
//        User::round += 2;
//        int winUser = User::listOfUsers[0]->sumOfWinRound[0];
//        QString winUserString = QString::number(winUser);
//        QString winWindow = MainWindow::listOfWindow[0]->reciveWin();
//        int winUser2 = User::listOfUsers[1]->sumOfWinRound[1];
//        QString winUserString2 = QString::number(winUser2);
//        QString winWindow2 = MainWindow::listOfWindow[1]->reciveWin();
//        if(User::countOfWinUser[0] == winWindow.toInt()){
//            if(winWindow.toInt() == 0){
//                winUser += 10 * (User::round/2);
//                User::listOfUsers[0]->sumOfWinRound[0] = winUser;
//                qDebug() << "player 11111111111111111111111111  win";
//                winUser2 -= 10 * (User::round/2);
//                User::listOfUsers[1]->sumOfWinRound[1] = winUser2;
//            }
//            else{
//                winUser += 10 * User::countOfWinUser[0];
//                User::listOfUsers[0]->sumOfWinRound[0] = winUser;
//                qDebug() << "player 11111111111111111111111111  win";
//                winUser2 -= 10 * User::countOfWinUser[1];
//                User::listOfUsers[1]->sumOfWinRound[1] = winUser2;
//            }
//        }
//        else if(User::countOfWinUser[1] == winWindow2.toInt()){
//            if(winWindow2.toInt() == 0){
//                winUser2 += 10 * (User::round / 2);
//                User::listOfUsers[1]->sumOfWinRound[1] = winUser2;
//                qDebug() << "player 2222222222222222222222222 win";
//                winUser -= 10 * (User::round / 2);
//                User::listOfUsers[0]->sumOfWinRound[0] = winUser;
//            }
//            else{
//                winUser2 += 10 * User::countOfWinUser[1];
//                User::listOfUsers[1]->sumOfWinRound[1] = winUser2;
//                qDebug() << "player 2222222222222222222222222 win";
//                winUser -= 10 * User::countOfWinUser[0];
//                User::listOfUsers[0]->sumOfWinRound[0] = winUser;
//            }
//        }
//        else{
//            winUser -= 10 * User::countOfWinUser[0];
//            User::listOfUsers[0]->sumOfWinRound[0] = winUser;

//            winUser2 -= 10 * User::countOfWinUser[1];
//            User::listOfUsers[1]->sumOfWinRound[1] = winUser2;
//            qDebug() << "no body winnnnnnnnnnnnnnnnnnnnnnnn";
//        }
//        if(User::round == 14){ // end of game
//            if(User::sumOfWinRound[0] > User::sumOfWinRound[1]){
//                qDebug() << "player 111111111111111111111111  win";
//                QMessageBox::information(this,"winner",User::listOfUsers[0]->getUserName() + " win the game");
//            }
//            else{
//                QMessageBox::information(this,"winner",User::listOfUsers[1]->getUserName() + " win the game");
//                qDebug() << "player 222222222222222222222222  win";
//            }
//        }
//        MainWindow::listOfWindow.clear();
//        QTimer::singleShot(300, [=]() {
//            //qDebug() << "showwwww";
//            User::listOfUsers[0]->send_message_for_round("end round");
//        });
//        qDebug() << "if forrrrr toundddd";
//    }

}

void MainWindow::reciveCard(QString imgg)
{
    qDebug() << "recive card ..... " << temp->getUserName();

        QString imgTmp;
        for(int i=0;i<imgg.size()-5;i++){
            imgTmp += imgg.at(i);
        }
        int index = imgg.size() - 2;
        QString power(imgg.at(index));
        QMessageBox::information(this,"card played " + temp->getUserName(),imgTmp + "  power : " + power);

        qDebug() << "after recive cardddddddddddddd";
//    //QString name;

//    //QMessageBox::information(this,"card played",);
//    centralWidget = new QWidget(this);
//    setCentralWidget(centralWidget); // centralWidget

//    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

//    QGridLayout *layout = new QGridLayout();
//    mainLayout->addLayout(layout);
//    QGridLayout *layout2 = new QGridLayout();
//    mainLayout->addLayout(layout2);

//    int row = 0;
//    QString tmp;

//    QString imgTmp = ":/res/";
//    for(int i=0;i<imgg.size()-1;i++){
//        imgTmp += imgg.at(i);
//    }
//    CardWidget *card = new CardWidget(imgTmp,this);

//    for(int i=0;i<temp->current_hand.size();i++){
//        //if(temp->current_hand.at(i) != imgg){
//            int sizeInside = temp->current_hand[i].size();
//            QString number = temp->current_hand[i][sizeInside - 1];

//            for(int j=0;j<sizeInside - 1;j++){
//                tmp += temp->current_hand[i][j];
//            }

//            qDebug() << "img : " << tmp;
//            QString img2 = ":/res/"+tmp;
//            //QString imgTmp = ":/res/"+imgg;
//            QIcon icon(img2);
//            QPushButton* btn = new QPushButton(this);
//            btn->setIcon(icon);
//            btn->setIconSize(icon.actualSize(QSize(180, 70)));
//            QString nn = QString::number(i);

//            //btn->setObjectName(nn);
//            connect(btn,&QPushButton::clicked,this,&MainWindow::onClickButton);


//            btn->setText(number);
//            //button.push_back(btn);


//            layout->addWidget(btn, row, 4, 1, 2);
//            layout->setAlignment(btn, Qt::AlignLeft);
//            layout->setContentsMargins(70, 50, 50, 50);
//            row++;

//            tmp = "";
//        //}
//    }
//    layout->addWidget(card,row,7);

    //resize(1450,1000);
    //this->show();






//    QString name,power;
//    for(int i=0;i<img.size() - 1;i++){
//        name += img[i];
//    }
//    power = img.at(img.size() - 1);  // label

//    QString imgPath = ":/res/"+name;
//    qDebug() << "pathhhhhhh " << imgPath;
//    CardWidget *card = new CardWidget(imgPath,this);
//    //QLabel *label = new QLabel(power, this);

//    //QWidget *centralWidget = new QWidget(this);
//    setCentralWidget(centralWidget); // centralWidget

//    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

//    QGridLayout *layout = new QGridLayout(this);
//    mainLayout->addLayout(layout);

//    layout->addWidget(card,3,7);
        //    //layout->addWidget(label,3,6);
}

QString MainWindow::reciveWin()
{
    QString result = le->text();
    qDebug() << "resulttttttt : " << result;
    return result;
}

void MainWindow::exitButton()
{
    listOfWindow[0]->close();
    listOfWindow[1]->close();
}

void MainWindow::change()
{
    qDebug() << "slot changeee";

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Confirmation", "Do you want to change your card randomly?",
                                  QMessageBox::Ok | QMessageBox::Cancel);

    if (reply == QMessageBox::Ok) {
        temp->send_message_for_round("change cards");
        MainWindow::listOfWindow[0]->showBoardGame();
        MainWindow::listOfWindow[1]->showBoardGame();
    }
    else {
       // nothing
    }

}

