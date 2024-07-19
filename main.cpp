#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "deck.hpp"
#include "card.hpp"
#include "Table.hpp"

using namespace std;




int main()
{
    Table *playingTable = new Table();
    playingTable->displayTable();

    Deck *playingDeck = new Deck();
    playingDeck->displayDeck();

    // Get Cards You Have
    cout << "Put The Cards You Have" << endl;
    playingTable->InitilizeAvilableCards(playingDeck);

    // Put Initial Cards
    cout << "Put initial Cards" << endl;
    playingTable->setupInitialCards(playingDeck);

    playingTable->displayDetails(playingDeck);

    // Display The Currently Avilable Cards
    // cout << "Currently Avilable Cards" << endl;
    // for (int i = 0; i < playingTable->getAvilableCards().size(); i++)
    // {
    //     playingTable->getAvilableCards().at(i)->display();
    // }
    // cout << endl;

    // Remove Card from the avilable Spot and Put it on the deck at ij
    // playingTable->putCardAtTable(playingDeck);

    // Remove Card Directly From Deck at Add to Table at ik
    // for (int i = 0; i < 5; i++)
    // {
    //     playingTable->putCardDirectlyFromDeck(playingDeck);
    // }

    int turn; // turn -> 0 1 2 3

    cout << "First turn is of : ";
    cin >> turn;

    while (1)
    {
        // When the turn is not mine
        if (turn != 0)
        {
            playingTable->putCardDirectlyFromDeck(playingDeck);
            turn = turn == 3 ? 0 : turn + 1;
            playingTable->displayDetails(playingDeck);
            continue;
        }

        // When the turn becomes mine

        // -> Get the optimalCard and optimal position
        optimalCardStructer *optimalCard = playingTable->optimalCard(playingDeck);
        int posx = optimalCard->posx;
        int posy = optimalCard->posy;
        int toPutCard = optimalCard->cardToPlay;

        cout << "The optimal Card to put is ";
        cout << playingTable->getAvilableCards().at(optimalCard->cardToPlay)->getRank() << " of " << playingTable->getAvilableCards().at(optimalCard->cardToPlay)->getSuit();
        cout << " at " << optimalCard->posx << " " << optimalCard->posy << endl;
        // Put the optimal Card automatically in the table


        playingTable->putCardAtTable(posx, posy, toPutCard, playingDeck);

        // Change the Turn to another player
        turn = 1;



        playingTable->displayDetails(playingDeck);
    }


}
