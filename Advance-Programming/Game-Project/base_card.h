#ifndef BASE_CARD_H
#define BASE_CARD_H

#include <QObject>
#include <QString>
#include <QPushButton>

class base_card : public QObject
{
    Q_OBJECT
public:
    explicit base_card(QString nam,int num,int pow,QObject *parent = nullptr);
    base_card();
    void set_power(QString x);
signals:

public slots:
private:
    int number;
    int power;
    QString name;
    QPushButton* x;
};

#endif // BASE_CARD_H
