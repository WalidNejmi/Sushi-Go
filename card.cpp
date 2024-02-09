/*
 * card.cpp
 * CS11 Sushi Go
 * Edited by: Walid Nejmi, wnejmi01
 */

#include "card.h"
#include <iostream>
using namespace std;

// Constructor: initialize the private field of a Card object
Card::Card(string c_name, int m_count) {
    card_name = c_name;
    maki_count = m_count;
    wasabi = false;
    already_traversed = false;
}

// Definition of the reset function
void Card::reset() {
    maki_count = 0;
    wasabi = false;
    already_traversed = false;
}
// getSushiType
// Output: Returns the sushi type (card_name) of the card.
string Card::getSushiType() {
    return card_name;
}

// getMakiCount
// Output: Returns the maki count (maki_count) of the card.
int Card::getMakiCount() {
    return maki_count;
}

// setAlreadyTraversed
// Input: Set the value of already_traversed to true.
void Card::setAlreadyTraversed() {
    already_traversed = true;
}

// setWasabi
// Input: Set the value of wasabi to true.
void Card::setWasabi() {
    wasabi = true;
}

// getSushiType
// Output: Returns the boolean value for whether we already traversed the card.
bool Card::getAlreadyTraversed() {
    return already_traversed;
}

// getSushiType
// Output: Returns the boolean value for whether the card is a Wasabi card.
bool Card::getWasabi() {
    return wasabi;
}