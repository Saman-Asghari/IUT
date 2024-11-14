#ifndef CHANGEINFORMATION_H
#define CHANGEINFORMATION_H

#include <QWidget>
#include <iostream>
#include <fstream>
#include <QMessageBox>

using namespace std;

namespace Ui {
class ChangeInformation;
}

class ChangeInformation : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeInformation(QWidget *parent = nullptr);
    ~ChangeInformation();

private slots:
    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::ChangeInformation *ui;
};

#endif // CHANGEINFORMATION_H
