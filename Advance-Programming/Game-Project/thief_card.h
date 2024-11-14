#ifndef THIEF_CARD_H
#define THIEF_CARD_H
#include "base_card.h"

class thief_card:virtual public base_card
{
private:
    QString info;
public:
    thief_card(QString nam,int num,int pow);
    QString get_info();
};

#endif // THIEF_CARD_H
