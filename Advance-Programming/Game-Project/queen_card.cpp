#include "queen_card.h"

queen_card::queen_card(QString nam, int num, int pow):base_card(nam,num,pow)
{
    this->info="kt";
}

QString queen_card::get_info()
{
    return info;
}
