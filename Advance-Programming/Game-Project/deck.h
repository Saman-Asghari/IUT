#ifndef DECK_H
#define DECK_H
#pragma once
#include <QObject>
#include "base_card.h"
#include "king_card.h"
#include "queen_card.h"
#include "thief_card.h"
#include <QVector>
class deck : public QObject
{
    Q_OBJECT
public:
    explicit deck(QObject *parent = nullptr);
    void set_cards();//will be completed
    void set_number_of_cards(int x);
    int get_number_of_cards();
    void set_won();
    int get_won();
signals:

public slots:
private:
    QVector<base_card*> cards;
    int number_of_card;
    int won;//if win ++ if lose nothing
};

#endif // DECK_H
