#include "base_card.h"

base_card::base_card(QString nam,int num,int pow,QObject *parent) : QObject(parent)
{
    this->power=pow;
    this->name=nam;
    this->number=num;
    set_power(nam);
}

base_card::base_card()
{

}

void base_card::set_power(QString x)
{
    if(x=="pirate"||x=="treasure"||x=="map"){
        this->power=1;
    }
    if(x=="flag"){
        this->power=2;
    }
    if(x=="king"||x=="queen"||x=="thief"){
        this->power=-1;
    }
}
