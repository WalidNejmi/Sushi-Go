/*
 * card.h
 * Walid Nejmi
 * Date: 11/8/2023
 * Purpose: Define a Card class to represent cards in the Rack-O game.
 *
 */
#ifndef _CARD_H
#define _CARD_H

#include <string>
using namespace std;

class Card {
public:
    // Constructor
    Card(string c_name, int m_count);
    // Getter
    string getSushiType();
    int getMakiCount();
    void setAlreadyTraversed();
    void setWasabi();
    bool getAlreadyTraversed();
    bool getWasabi();
    void reset();
private:
    // The name of the card
    string card_name;
    int maki_count;
    bool wasabi;
    bool already_traversed;
};

#endif // _CARD_H
