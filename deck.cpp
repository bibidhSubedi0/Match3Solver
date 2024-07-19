#include "deck.hpp"

Deck::Deck()
{
    this->suits = {"h", "d", "c", "s"},
    this->ranks = {1,2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    for(int i=0;i<suits.size();i++)
    {
        for(int j=0;j<ranks.size();j++)
        {
            Card *k = new Card(ranks[j],suits[i]);
            cards.push_back(k);
        }
    }
}


void Deck::displayDeck()
{

    string LastSuite = cards[0]->getSuit();
    for(int i=0;i<cards.size()-1;i++)
    {
        cards[i]->display();
        LastSuite = cards[i]->getSuit();
        if(LastSuite != cards[i+1]->getSuit())
        {
            cout<<endl;
            LastSuite =cards[i+1]->getSuit();
        }
    }
    cards[cards.size()-1]->display();
    cout<<endl;
}

vector<Card *> &Deck::getDeck()
{
    return cards;
}