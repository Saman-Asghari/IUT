#include "king_card.h"

king_card::king_card(QString nam, int num, int power):base_card(nam,num,power)
{
    this->info="tq";//first letter is the one who king can beat and the second one is the ne who can beat king
}

QString king_card::get_info()
{
    return info;
}
