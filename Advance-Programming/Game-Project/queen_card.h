#ifndef QUEEN_CARD_H
#define QUEEN_CARD_H
#include "base_card.h"

class queen_card:virtual public base_card
{
private:
    QString info;
public:
    queen_card(QString nam,int num,int pow);
    QString get_info();
};

#endif // QUEEN_CARD_H
