#ifndef KING_CARD_H
#define KING_CARD_H
#include "base_card.h"
#include <QVector>
class king_card:virtual public base_card
{
private:
    QString info;
public:
    king_card(QString nam,int num,int power);
    QString get_info();
};

#endif // KING_CARD_H
