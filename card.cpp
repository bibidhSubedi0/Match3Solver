#include "card.hpp"

Card::Card(int r, string s)
{
    this->rank = r;
    this->suit = s;
}

void Card::display()
{
    cout << rank << " " << suit<<"\t";
}


int Card::getRank()
{
    return rank;
}

string Card::getSuit()
{
    return suit;
}