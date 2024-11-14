#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QObject>
#include "cardwidget.h"
#include "user.h"
#include <QVector>


using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(){

    };
    MainWindow(User*x,QWidget *parent = nullptr);
    void startTheGameByToti(int n1,int n2); // choose who first start
    QVector<QVector<QString>> source_cards;
    static vector<QString> hideCards;
    void setplayersrandomcard(QVector<QVector<QString>> x);
    void showBoardGame();
    void chooseWinner();
    static int countForCard;
    static int check;
    static QVector<MainWindow*> listOfWindow;
    static int sendClientForChooseWin;
    QWidget* centralWidget;
    QLineEdit* le;
    QPushButton* exit;
    QPushButton* changeCard;

    void closeEvent(QCloseEvent* event) override;




signals:

public slots:
    int onClickButton();
    void reciveCard(QString img);
    QString reciveWin();
    void exitButton();
    void change();


private:
    User* temp;
    vector<QPushButton*> button;
};

#endif MAINWINDOW_H
