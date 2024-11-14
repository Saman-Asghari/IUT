#ifndef CHOOSECLIENT_H
#define CHOOSECLIENT_H

#include <QWidget>
#include <fstream>
#include "user.h"



using namespace std;


namespace Ui {
class ChooseClient;
}

class ChooseClient : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseClient(QWidget *parent = nullptr);
    ~ChooseClient();
    static QString usernameChooseClient;


private slots:
    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::ChooseClient *ui;
};

#endif // CHOOSECLIENT_H

