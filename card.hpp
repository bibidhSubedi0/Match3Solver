#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <vector>
#include <iostream>

using namespace std;

// Define a Card class
class Card
{
private:
    string suit;
    int rank;

public:
    Card(int r, string suit);

    // For displaying the card
    void display();
    int getRank();
    string getSuit();
};

#endif // CARD_HPP