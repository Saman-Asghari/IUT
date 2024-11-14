#include "thief_card.h"

thief_card::thief_card(QString nam, int num, int pow):base_card(nam,num,pow)
{
    this->info="qk";
}

QString thief_card::get_info()
{
    return info;
}

