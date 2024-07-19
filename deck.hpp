#ifndef DECK_HPP
#define DECK_HPP

#include"card.hpp"

class Deck {
private:
    vector<Card*> cards;
    vector<string> suits;
    vector<int> ranks;

public:
    Deck();


    // Function to display the deck
    void displayDeck();
    vector<Card*> &getDeck();
};

#endif