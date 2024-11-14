#include "deck.h"

deck::deck(QObject *parent) : QObject(parent)
{

}

void deck::set_cards()
{

}

void deck::set_number_of_cards(int x)
{
    number_of_card=x;
}

int deck::get_number_of_cards()
{
    return number_of_card;
}

void deck::set_won()
{
    this->won++;

}

int deck::get_won()
{
    return won;
}

