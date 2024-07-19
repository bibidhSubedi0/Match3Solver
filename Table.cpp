#include "Table.hpp"
#include "deck.hpp"
#include <algorithm>

Table::Table()
{

    Card *ul = new Card(0, " x");
    for (int r = 0; r < 5; r++)
    {
        vector<Card *> thisRow;
        for (int c = 0; c < 8; c++)
        {
            thisRow.push_back(ul);
        }
        playingTable.push_back(thisRow);
    }
    // delete(ul);
}

optimalCardStructer ::optimalCardStructer(int posx, int posy, int cardToPlay, int maxPoints) : posx(posx), posy(posy), cardToPlay(cardToPlay), maxPoints(maxPoints) {}

void Table::displayTable()
{
    for (int r = 0; r < playingTable.size(); r++)
    {
        for (int c = 0; c < playingTable[r].size(); c++)
        {
            playingTable.at(r).at(c)->display();
            // playingTable[r][c]->display();
        }
        cout << " \n\n";
    }
}

cardInfo::cardInfo(Card *k, int posx, int posy) : k(k), posx(posx), posy(posy){};

void Table::putInitialCards(vector<cardInfo *> toPut)
{
    for (int i = 0; i < toPut.size(); i++)
    {
        Card *temp = new Card(toPut[i]->k->getRank(), toPut[i]->k->getSuit());
        playingTable[toPut[i]->posx][toPut[i]->posy] = temp;
    }
}

void Table::setupInitialCards(Deck *playingDeck)
{
    vector<cardInfo *> toPut;

    for (int i = 1; i <= 2; i++)
    {
        for (int j = 2; j <= 3; j++)
        {
            int R;
            string S;
            cout << "Enter Rank of card at " << i << j << endl;
            cin >> R;
            cout << "Enter Suit of card at " << i << j << endl;
            cin >> S;

            Card *temp_card = new Card(R, S);

            for (int k = 0; k < playingDeck->getDeck().size(); k++)
            {
                if ((playingDeck->getDeck().at(k)->getRank() == R) && (playingDeck->getDeck().at(k)->getSuit() == S))
                {
                    playingDeck->getDeck().erase(playingDeck->getDeck().begin() + k);
                    break;
                }
            }

            cardInfo *temp = new cardInfo(temp_card, i, j);
            toPut.push_back(temp);
        }
    }

    // vector<cardInfo *> toPut = {};

    // for (int i = 1; i <= 2; i++)
    // {
    //     for (int j = 2; j <= 3; j++)
    //     {
    //         Card *temp_card = new Card(i * j, "d");
    //         for (int k = 0; k < playingDeck->getDeck().size(); k++)
    //         {
    //             if ((playingDeck->getDeck().at(k)->getRank() == temp_card->getRank()) && (playingDeck->getDeck().at(k)->getSuit() == temp_card->getSuit()))
    //             {
    //                 playingDeck->getDeck().erase(playingDeck->getDeck().begin() + k);
    //                 break;
    //             }
    //         }
    //         cardInfo *temp = new cardInfo(temp_card, i, j);
    //         toPut.push_back(temp);
    //     }
    // }

    putInitialCards(toPut);
}

void Table::InitilizeAvilableCards(Deck *playingDeck)
{
    for (int i = 0; i < 4; i++)
    {
        int R;
        string S;
        cout << "Enter Rank of card at " << i + 1 << endl;
        cin >> R;
        cout << "Enter Suit of card at " << i + 1 << endl;
        cin >> S;

        Card *temp_card = new Card(R, S);
        // Card *temp_card = new Card(i + 7, "d");

        avilableCards.push_back(temp_card);
    }
}

vector<Card *> Table::getAvilableCards()
{
    return avilableCards;
}

void Table::putCardAtTable(int toPutRow, int toPutCol, int toPutCard, Deck *playingDeck)
{

    Card *tempK = new Card(avilableCards[toPutCard]->getRank(), avilableCards[toPutCard]->getSuit());

    playingTable.at(toPutRow).at(toPutCol) = tempK;

    for (int k = 0; k < playingDeck->getDeck().size(); k++)
    {
        if ((playingDeck->getDeck().at(k)->getRank() == tempK->getRank()) && (playingDeck->getDeck().at(k)->getSuit() == tempK->getSuit()))
        {
            playingDeck->getDeck().erase(playingDeck->getDeck().begin() + k);
            break;
        }
    }

    int R;
    string S;
    cout << "Enter Rank of New card " << endl;
    cin >> R;
    cout << "Enter Suit of New card " << endl;
    cin >> S;

    Card *tk = new Card(R, S);
    avilableCards[toPutCard] = tk;
}

void Table::putCardDirectlyFromDeck(Deck *playingDeck)
{
    int row, col;
    int R;
    string S;
    cout << "Enter Rank of card " << endl;
    cin >> R;
    cout << "Enter Suit of ard " << endl;
    cin >> S;
    cout << "Enter Row" << endl;
    cin >> row;
    cout << "Enter Col" << endl;
    cin >> col;

    Card *temp_card = new Card(R, S);
    playingTable.at(row).at(col) = temp_card;
    for (int k = 0; k < playingDeck->getDeck().size(); k++)
    {
        if ((playingDeck->getDeck().at(k)->getRank() == temp_card->getRank()) && (playingDeck->getDeck().at(k)->getSuit() == temp_card->getSuit()))
        {
            playingDeck->getDeck().erase(playingDeck->getDeck().begin() + k);
            break;
        }
    }
}

void Table::displayDetails(Deck *playingDeck)
{
    cout << "-------------------------------------------------------------" << endl;
    cout << "-------------------------------------------------------------" << endl;
    displayTable();
    cout << "-------------------------------------------------------------" << endl;
    playingDeck->displayDeck();
    cout << "-------------------------------------------------------------" << endl;
    cout << "Currently Avilable Cards" << endl;
    for (int i = 0; i < getAvilableCards().size(); i++)
    {
        getAvilableCards().at(i)->display();
    }
    cout << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << "-------------------------------------------------------------" << endl;
}

optimalCardStructer *Table::optimalCard(Deck *playingDeck)
{
    optimalCardStructer *optCard = new optimalCardStructer(0, 0, 0, 0);

    for (int k = 0; k < 4; k++)
    {
        for (int r = 0; r < 5; r++)
        {
            for (int c = 0; c < 8; c++)
            {
                int p = maxPointsAtij(r, c, k);
                // cout << "Points at " << r << " " << c << " for " << avilableCards[k]->getRank() << " of " << avilableCards[k]->getSuit() << " is " << p << endl;
                if (p > optCard->maxPoints)
                {
                    optCard->posx = r;
                    optCard->posy = c;
                    optCard->cardToPlay = k;
                    optCard->maxPoints = p;
                }
            }
        }
    }

    return optCard;
}

coodrinates::coodrinates(int posx, int posy) : posx(posx), posy(posy) {}

int Table::maxPointsAtij(int r, int c, int k)
{
    if (playingTable.at(r).at(c)->getRank() != 0)
        return 0;

    int left, right, top, bottom, topLeft, topRight, bottomLeft, bottomRight, vertical, horizontal;
    left = checkLeft(r, c, k);

    right = checkRight(r, c, k);
    top = checkTop(r, c, k);

    bottom = checkBottom(r, c, k);

    topLeft = checkTopLeft(r, c, k);
    topRight = checkTopRight(r, c, k);
    bottomLeft = checkBootmLeft(r, c, k);
    bottomRight = checkBottomRight(r, c, k);
    vertical = checkVertical(r, c, k);
    horizontal = checkHorizontal(r, c, k);

    int multiplier = 0;
    if (left != 0)
        multiplier += 1;
    if (right != 0)
        multiplier += 1;
    if (top != 0)
        multiplier += 1;
    if (bottom != 0)
        multiplier += 1;
    if (bottomLeft != 0)
        multiplier += 1;
    if (bottomRight != 0)
        multiplier += 1;
    if (topLeft != 0)
        multiplier += 1;
    if (vertical != 0)
        multiplier += 1;
    if (topRight != 0)
        multiplier += 1;
    if (horizontal != 0)
        multiplier += 1;

    return (left + right + top + bottom + topLeft + topRight + bottomLeft + bottomRight + vertical + horizontal) * multiplier;
}

bool isValid(coodrinates c1, coodrinates c2)
{
    return (c1.posx >= 0 && c1.posx <= 4 && c1.posy >= 0 && c1.posy <= 7 && c2.posx >= 0 && c2.posx <= 4 && c2.posy >= 0 && c2.posy <= 7);
}

int Table::getPointsAtc1c2(coodrinates c1, coodrinates c2, int k)
{

    if (!isValid(c1, c2))
        return 0;

    if (checkTrail(c1, c2, k))
        return 100;
    if (checkDoubleSequence(c1, c2, k))
        return 60;
    if (checkSequence(c1, c2, k))
        return 40;
    if (checkColor(c1, c2, k))
        return 20;
    if (checkPair(c1, c2, k))
        return 10;

    return 0;
}

int Table::checkLeft(int r, int c, int k)
{
    coodrinates c1(r, c - 2);
    coodrinates c2(r, c - 1);

    return getPointsAtc1c2(c1, c2, k);
}

int Table::checkRight(int r, int c, int k)
{
    coodrinates c1(r, c + 2);
    coodrinates c2(r, c + 1);
    return getPointsAtc1c2(c1, c2, k);
}

int Table::checkTop(int r, int c, int k)
{
    coodrinates c1(r - 2, c);
    coodrinates c2(r - 1, c);
    return getPointsAtc1c2(c1, c2, k);
}

int Table::checkBottom(int r, int c, int k)
{

    coodrinates c1(r + 2, c);
    coodrinates c2(r + 1, c);
    return getPointsAtc1c2(c1, c2, k);
}

int Table::checkTopLeft(int r, int c, int k)
{
    coodrinates c1(r - 2, c - 2);
    coodrinates c2(r - 1, c - 1);
    return getPointsAtc1c2(c1, c2, k);
}

int Table::checkTopRight(int r, int c, int k)
{
    coodrinates c1(r - 2, c + 2);
    coodrinates c2(r - 1, c + 1);
    return getPointsAtc1c2(c1, c2, k);
}

int Table::checkBootmLeft(int r, int c, int k)
{
    coodrinates c1(r + 2, c - 2);
    coodrinates c2(r + 1, c - 1);
    return getPointsAtc1c2(c1, c2, k);
}

int Table::checkBottomRight(int r, int c, int k)
{
    coodrinates c1(r + 2, c + 2);
    coodrinates c2(r + 1, c + 1);
    return getPointsAtc1c2(c1, c2, k);
}

int Table::checkVertical(int r, int c, int k)
{
    coodrinates c1(r - 1, c);
    coodrinates c2(r + 1, c);
    return getPointsAtc1c2(c1, c2, k);
}

int Table::checkHorizontal(int r, int c, int k)
{
    coodrinates c1(r, c - 1);
    coodrinates c2(r, c + 1);
    return getPointsAtc1c2(c1, c2, k);
}

bool Table::checkTrail(const coodrinates &c1, const coodrinates &c2, int k)
{
    // cout<<"Trail : "<<endl;
    return ((playingTable.at(c1.posx).at(c1.posy)->getRank() == avilableCards[k]->getRank()) && (playingTable.at(c2.posx).at(c2.posy)->getRank() == avilableCards[k]->getRank()));
}
bool Table::checkDoubleSequence(const coodrinates &c1, const coodrinates &c2, int k)
{
    // cout<<"DS : "<<endl;
    return (checkSequence(c1, c2, k) && checkColor(c1, c2, k));
}
bool Table::checkSequence(const coodrinates &c1, const coodrinates &c2, int k)
{
    // cout<<"S : "<<endl;
    // Get the cards at coordinates c1 and c2

    int a = playingTable.at(c1.posx).at(c1.posy)->getRank();
    int b = playingTable.at(c2.posx).at(c2.posy)->getRank();
    int c = avilableCards[k]->getRank();
    if (a == 0 || b == 0 || c == 0)
        return 0;
    int numbers[] = {a, b, c};

    std::sort(numbers, numbers + 3);

    return (numbers[1] == numbers[0] + 1) && (numbers[2] == numbers[1] + 1);
}

bool Table::checkColor(const coodrinates &c1, const coodrinates &c2, int k)
{
    // cout<<"Color : "<<endl;
    return ((playingTable.at(c1.posx).at(c1.posy)->getSuit() == avilableCards[k]->getSuit()) && (playingTable.at(c2.posx).at(c2.posy)->getSuit() == avilableCards[k]->getSuit()));
}
bool Table::checkPair(const coodrinates &c1, const coodrinates &c2, int k)
{
    // cout<<"P : "<<endl;
    return (
        ((playingTable.at(c1.posx).at(c1.posy)->getRank() == avilableCards[k]->getRank() && ((playingTable.at(c2.posx).at(c2.posy)->getRank() != 0)))) ||
        ((playingTable.at(c2.posx).at(c2.posy)->getRank() == avilableCards[k]->getRank() && ((playingTable.at(c1.posx).at(c1.posy)->getRank() != 0)))) ||
        ((playingTable.at(c1.posx).at(c1.posy)->getRank() == playingTable.at(c2.posx).at(c2.posy)->getRank()) && ((playingTable.at(c1.posx).at(c1.posy)->getRank() != 0))));
}
