#ifndef TABLE_HPP
#define TABLE_HPP
#include "card.hpp"
#include "deck.hpp"
#include <map>
#include <string>

struct cardInfo
{
    Card *k;
    int posx;
    int posy;

    cardInfo(Card *k, int posx, int posy);
};

struct optimalCardStructer
{
    int posx;
    int posy;
    int cardToPlay;
    int maxPoints;

    optimalCardStructer(int posx, int posy, int cardToPlay, int maxPoints);
};

struct coodrinates
{
    int posx;
    int posy;

    coodrinates(int posx, int posy);
};

class Table
{
    vector<vector<Card *>> playingTable;
    vector<Card *> avilableCards;

    //
    map<string, int> points{{"t", 100}, {"ds", 60}, {"s", 40}, {"c", 20}, {"p", 10}};


public:
    Table();
    void displayTable();
    void setupInitialCards(Deck *playingDeck);
    void putInitialCards(vector<cardInfo *> toPut);
    void InitilizeAvilableCards(Deck *playingDeck);
    vector<Card *> getAvilableCards();
    void putCardAtTable(int toPutRow, int toPutCol, int toPutCard, Deck *playingDeck);
    void putCardDirectlyFromDeck(Deck *playingDeck);
    optimalCardStructer *optimalCard(Deck *playingDeck);

    void displayDetails(Deck *playingDeck);
    int maxPointsAtij(int r, int c, int k);
    int calculatePoints();
    void resetOocurance();

    int checkLeft(int r, int c, int k);
    int checkRight(int r, int c, int k);
    int checkTop(int r, int c, int k);
    int checkBottom(int r, int c, int k);
    int checkTopLeft(int r, int c, int k);
    int checkTopRight(int r, int c, int k);
    int checkBootmLeft(int r, int c, int k);
    int checkBottomRight(int r, int c, int k);
    int checkVertical(int r, int c, int k);
    int checkHorizontal(int r, int c, int k);

    bool checkTrail(const coodrinates& c1, const coodrinates& c2,int k);
    bool checkDoubleSequence(const coodrinates& c1, const coodrinates& c2,int k);
    bool checkSequence(const coodrinates& c1, const coodrinates& c2,int k);
    bool checkColor(const coodrinates& c1, const coodrinates& c2,int k);
    bool checkPair(const coodrinates& c1, const coodrinates& c2,int k);
    


    int getPointsAtc1c2(coodrinates c1, coodrinates c2, int k);
};

#endif