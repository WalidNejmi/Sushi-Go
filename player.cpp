/*
 * player.cpp
 * Edited by: Walid Nejmi, wnejmi01
 * CS11 Sushi Go
 */

#include "player.h"
#include "vector.h"

// Player Constructor
// Description: Initializes a Player object with default values.
// Purpose: Sets score to 0, pudding count to 0, selected card to nullptr,
//           temp selected card to nullptr, and creates an empty hand.
Player::Player() {
    selected_card = nullptr;
    selected_card_2 = nullptr;
    temp_selec = nullptr;
    temp_selec_2 = nullptr;
    hand = new Vector();
}

//resetPlayer
// reset the variables in the Player class
void Player::resetPlayer() {
    selected_card = nullptr;
    temp_selec = nullptr;
    for (int i = 0; i < selected_cards.size(); i++) {
        if (selected_cards.at(i) != nullptr) {
            delete selected_cards.at(i);
        }
    }
    for (int i = 0; i < hand->size(); i++) {
        if (hand->at(i) != nullptr) {
            delete hand->at(i);
        }
    }  
    if (hand != nullptr) {
        delete hand;
    }   
    hand = new Vector();
    selected_cards.resetV(); 
    number_maki = 0;
    tempura_count = 0;
    sashimi_count = 0;
    dumpling_count = 0;
    nigiri_count = 0; 
    n_salmon = 0;
    n_egg = 0;
    n_squid = 0;
    wasabi_count = 0;
    round_score = 0;
    maki_score = 0;
    tempura_score = 0;
    sashimi_score = 0;
    dumpling_score = 0;
    nigiri_score = 0;
    wasabi_score = 0;
    chopstick = false;
}


// Player Destructor
// Purpose: Deallocates memory for selected_card, temp_selec, and the hand.
Player::~Player() {

    for (int i = 0; i < selected_cards.size(); i++) {
        if (selected_cards.at(i) != nullptr) {
            delete selected_cards.at(i);
        }

    }
    for (int i = 0; i < hand->size(); i++) {
        if (hand->at(i) != nullptr) {
            delete hand->at(i);
        }
    }
    
    if (hand != nullptr) {
        delete hand;
    }
}

//                            Getters                 

// getPassingHand
// Input: None
// Output: Returns a pointer to the player's hand.
Vector *Player::getPassingHand() {
    return hand;
}

// getScore
// Output: Returns the player's score.
int Player::getScore() {
    return total_score;
}

// getTemp
// Output: Returns a card pointer to the temporary card the player has selected.
Data Player::getTemp() {
    return temp_selec;
}

// getRevealedCards
// Input: None
// Output: Returns a pointer to the player's selected cards.
Vector *Player::getRevealedCards() {
    return &selected_cards;
}

// getSelectedCard
// Output: Returns the player's selected card.
Data Player::getSelectedCard() {
    return selected_card;
}

// getMakiCount
// Output: Returns the player's Maki count.
int Player::getMakiCount() {
    return number_maki;
}

// getTempuraCount
// Output: Returns the player's Tempura count.
int Player::getTempuraCount() {
    return tempura_count;
}

// getMashimiCount
// Output: Returns the player's Sashimi count.
int Player::getSashimiCount() {
    return sashimi_count;
}

// getDumplingCount
// Output: Returns the player's Dumpling count.
int Player::getDumplingCount() {
    return dumpling_count;
}

// getNigiriCount
// Output: Returns the player's Nigiri count.
int Player::getNigiriCount() {
    return nigiri_count;
}

// getSalmonCount
// Output: Returns the player's Salmon-Nigiri count.
int Player::getSalmonCount() {
    return n_salmon;
}

// getEggCount
// Output: Returns the player's Egg-Nigiri count.
int Player::getEggCount() {
    return n_egg;
}

// getSquidCount
// Output: Returns the player's Squid-Nigiri count.
int Player::getSquidCount() {
    return n_squid;
}


// getWasabiCount
// Output: Returns the player's Wasabi count.
int Player::getWasabiCount() {
    return wasabi_count;
}

// getPuddingCount
// Output: Returns the player's Pudding count.
int Player::getPuddingCount() {
    return pudding_count;
}



// getMakiScore
// Output: Returns the player's Maki score.
int Player::getMakiScore() {
    return maki_score;
}

// getTempuraScore
// Output: Returns the player's Tempura score.
int Player::getTempuraScore() {
    return tempura_score;
}

// getMashimiScore
// Output: Returns the player's Sashimi score.
int Player::getSashimiScore() {
    return sashimi_score;
}

// getDumplingScore
// Output: Returns the player's Dumpling score.
int Player::getDumplingScore() {
    return dumpling_score;
}

// getNigiriScore
// Output: Returns the player's Nigiri score.
int Player::getNigiriScore() {
    return nigiri_score;
}

// getWasabiScore
// Output: Returns the player's Wasabi score.
int Player::getWasabiScore() {
    return wasabi_score;
}

// getPuddingScore
// Output: Returns the player's Pudding score.
int Player::getPuddingScore() {
    return pudding_score;
}


//                            Setters                     

// setPassingH
// Input: Pointer to a Vector object (h).
// Purpose: Sets the player's hand to the provided Vector.
// Output: void
void Player::setPassingH(Vector *h) {
    hand = h;
}

// erasePassingCard
// Input: Index of the card to be erased.
// Purpose: Erases the card at the specified index from the player's hand.
// Output: void
void Player::erasePassingCard(int index) {
    hand->erase(index);

} 

void Player::eraseSelectedCard(int index) {
    selected_cards.erase(index);
}

void Player::insertPassingCard(int index, Card *c) {
    selected_cards.insert(index, c);
}
// setSelectedCard
// Input: Data object representing the selected card (c).
// Purpose: Sets the player's selected card to the provided value.
// Output: void
void Player::setSelectedCard(Data c) {
    selected_card = c;
}


// SetTemp
// Input: Pointer to a Card object (c).
// Modifies: Sets the player's temporary selected card to the provided value.
void Player::SetTemp(Card *c) {
    temp_selec = c;
}

// AddSelectedCards
// Input: Pointer to a Card object.
// Purpose: Adds the provided card to the player's selected cards.
void Player::AddSelectedCards(Card *card) {
    selected_cards.push_back(card);
}

// setMakiCount
// Purpose: Updates the player's Maki count.
void Player::setMakiCount() {
    for (int i = 0; i < selected_cards.size(); i++) {
        if (selected_cards.at(i)->getSushiType() == "Maki") {
            number_maki += 1;
        }
    }
}

// setTempuraCount
// Purpose: Updates the player's Tempura count.
void Player::setTempuraCount() {
    for (int i = 0; i < selected_cards.size(); i++) {
        if (selected_cards.at(i)->getSushiType() == "Tempura") { 
            tempura_count += 1;
        }
    }
}


// setMashimiCount
// Purpose: Updates the player's Sashimi count.
void Player::setSashimiCount() {
    for (int i = 0; i < selected_cards.size(); i++) {
        if (selected_cards.at(i)->getSushiType() == "Sashimi") {
            sashimi_count += 1;
        }
    }
}

// setDumplingCount
// Purpose: Updates the player's Dumpling count.
void Player::setDumplingCount() {
    for (int i = 0; i < selected_cards.size(); i++) {
        if (selected_cards.at(i)->getSushiType() == "Dumpling") {
            dumpling_count += 1;
        }
    }
}

// setNigiriCount
// Purpose: Updates the player's Nigiri count.
void Player::setNigiriCount() {
    for (int i = 0; i < selected_cards.size(); i++) {
        if (selected_cards.at(i)->getSushiType() == "Salmon-Nigiri"
        && !selected_cards.at(i)->getAlreadyTraversed()) {
            n_salmon += 1;
            nigiri_count += 1;
        }
        else if (selected_cards.at(i)->getSushiType() == "Egg-Nigiri"
        && !selected_cards.at(i)->getAlreadyTraversed()) {
            n_egg += 1;
            nigiri_count += 1;
        }
        else if (selected_cards.at(i)->getSushiType() == "Squid-Nigiri"
        && !selected_cards.at(i)->getAlreadyTraversed()) {
            n_squid += 1;
            nigiri_count += 1;          
        }
    }
}

// setWasabiCount
// Purpose: Updates the player's Wasabi count.
void Player::setWasabiCount() {
    for (int i = 0; i < selected_cards.size(); i++) {
        if (selected_cards.at(i)->getSushiType() == "Wasabi"
        && !selected_cards.at(i)->getWasabi()) {
            wasabi_count += 1;
            selected_cards.at(i)->setWasabi();
        }
    }
}

// setPuddingCount
// Purpose: Updates the player's Pudding count.
void Player::setPuddingCount() {
    for (int i = 0; i < selected_cards.size(); i++) {
        if (selected_cards.at(i)->getSushiType() == "Pudding") {
            pudding_count += 1;
        }
    }
}

//countMaki
// Purpose: Calculate and updates the number of Maki a player has
// Output: None
void Player::countMaki() {
    for (int i = 0; i < selected_cards.size(); i++) {
        if (selected_cards.at(i)->getSushiType() == "Maki") {
            if (selected_cards.at(i)->getMakiCount() == 1) {
                number_maki += 1;
            }
            else if (selected_cards.at(i)->getMakiCount() == 2) {
                number_maki += 2;
            }
            else if (selected_cards.at(i)->getMakiCount() == 3) {
                number_maki += 3;
            }
        }
    }
}
// scoreTempura
// Purpose: Calculate and update the Tempura score for the player.
void Player::scoreTempura() {
    setTempuraCount();
    int pairs = tempura_count/2;
    tempura_score = pairs * 5;
}

// scoreSashimi
// Purpose: Calculate and update the Sashimi score for the player.
void Player::scoreSashimi() {
    setSashimiCount();
    int trio = sashimi_count/3;
    sashimi_score = trio * 10;

}

// scoreNigiri
// Purpose: Calculate and update the Nigiri score for the player.
void Player::scoreNigiri() {
    setNigiriCount();
    setWasabiCount();
    nigiri_score = n_egg + (n_salmon * 2) + (n_squid * 3);

    if (nigiri_count != 0 && wasabi_count != 0) {
        for (int i = 0; i < selected_cards.size(); i++) {
            if (selected_cards.at(i)->getSushiType() == "Egg-Nigiri") {
                eggWasabi(i);
            } else if (selected_cards.at(i)->getSushiType() == "Salmon-Nigiri"){
                salmonWasabi(i);
            } else if (selected_cards.at(i)->getSushiType() == "Squid-Nigiri") {
                squidWasabi(i);
            }
        }
    }
    
}

// eggWasabi
// Purpose: Calculate and update the score for Egg-Nigiri with Wasabi.
// Input: Index i of the selected card
void Player::eggWasabi(int i) {
    if (!selected_cards.at(i)->getAlreadyTraversed()) {
        for (int j = 0; j < selected_cards.size(); j++) {
            // Check whether the Wasabi and nigiri cards have been used
            if (selected_cards.at(j)->getSushiType() == "Wasabi" &&  
                !selected_cards.at(i)->getAlreadyTraversed() &&
                !selected_cards.at(j)->getAlreadyTraversed() &&
                j < i) {
                nigiri_score += 2;
                selected_cards.at(i)->setAlreadyTraversed();
                selected_cards.at(j)->setAlreadyTraversed();
            }
        }
    }
}

// salmonWasabi
// Purpose: Calculate and update the score for Salmon-Nigiri with Wasabi.
// Input: Index i of the selected card
void Player::salmonWasabi(int i) {  
    if (!selected_cards.at(i)->getAlreadyTraversed()) {
        for (int j = 0; j < selected_cards.size(); j++) {
            // Check whether the Wasabi and nigiri cards have been used
            if (selected_cards.at(j)->getSushiType() == "Wasabi" &&
                !selected_cards.at(i)->getAlreadyTraversed() &&
                !selected_cards.at(j)->getAlreadyTraversed() &&
                j < i) {
                nigiri_score += 4;
                selected_cards.at(i)->setAlreadyTraversed();
                selected_cards.at(j)->setAlreadyTraversed();
            }
        }
    }   
}

// squidWasabi
// Purpose: Calculate and update the score for Squid-Nigiri with Wasabi.
// Input: Index i of the selected card
void Player::squidWasabi(int i) {
    if (!selected_cards.at(i)->getAlreadyTraversed()) {
        for (int j = 0; j < selected_cards.size(); j++) {
            // Check whether the Wasabi and nigiri cards have been used
            if (selected_cards.at(j)->getSushiType() == "Wasabi" &&
                !selected_cards.at(i)->getAlreadyTraversed() &&
                !selected_cards.at(j)->getAlreadyTraversed() &&
                j < i) {
                nigiri_score += 6;
                selected_cards.at(i)->setAlreadyTraversed();
                selected_cards.at(j)->setAlreadyTraversed();
            }
        }
    }
}


// setScore
// Purpose: Calculate and set the total score for the player.
void Player::setScore() {
    countMaki();
    scoreTempura();
    scoreSashimi();
    scoreDumpling();
    scoreNigiri();
    setPuddingCount();

    int determine_score = maki_score + tempura_score + sashimi_score + 
    dumpling_score + nigiri_score;

    round_score = determine_score;
    total_score += round_score;
}

// scoreDumpling
// Purpose: Calculate and update the Dumpling score for the player.
void Player::scoreDumpling() {
    setDumplingCount();
    if (dumpling_count == 1) {
        dumpling_score += 1;
    }

    else if (dumpling_count == 2) {
        dumpling_score += 3;
    }

    else if (dumpling_count == 3) {
        dumpling_score += 6;
    }

    else if (dumpling_count == 4) {
        dumpling_score += 10;
    }   

    else if (dumpling_count > 4) {
        dumpling_score += 15;
    }
}

// addMakiPoints
// Purpose: Add Maki points to the total score.
// Input: Points to be added
void Player::addMakiPoints(int points) {
    total_score += points;
}

// addPuddingPoints
// Purpose: Add Pudding points to the total score.
// Input: Points to be added
void Player::addPuddingPoints(int points) {
    total_score += points;
}

// setChopstick
// Purpose: set the value of Chopstick to true.
void Player::setChopstick() {
    chopstick = true;
}
// setChopstickF
// Purpose: set the value of Chopstick to false.
void Player::setChopstickF() {
    chopstick = false;
}
//getChopstick
// get the value of the boolean chopstick
bool Player::getChopstick() {
    return chopstick;
}

// getSelectedCards
// Get the vector of the selected cards of a player
Vector Player::getSelectedCards() {
    return selected_cards;
}
// SetTemp2
// Set the second selected card to a temporary value
void Player::SetTemp2(Card *c) {
    temp_selec_2 = c;
}

// GetTemp2
// Get the temporary value of the second selected card
Data Player::getTemp2() {
    return temp_selec_2;
}

// finChopsticks
// Purpose: returns the index of the card Chopsticks in a player's selected 
// cards.
int Player::findChopsticks(){
    for (int i = 0; i < selected_cards.size(); i++){
        if (selected_cards.at(i)->getSushiType() == "Chopsticks"){
            return i;
        }
    }
    return -1;
}

// finChopsticksP
// Purpose: returns the pointer of the card Chopsticks in a player's selected 
// cards.
Card *Player::findChopsticksP() {
    for (int i = 0; i < selected_cards.size(); i++){
        if (selected_cards.at(i)->getSushiType() == "Chopsticks"){
            return selected_cards.at(i);
        }
    }
    return nullptr;
}

// findChopsticksB
// Input: the player whose selected cards are checked for Chopsticks.
// Purpose: Find and return the Chopsticks card in the player's selected cards.
// Output: Returns a boolean
bool Player::findChopsticksB() {
    for (int i = 0; i < selected_cards.size(); i++) {
        if (selected_cards.at(i)->getSushiType() == "Chopsticks") {
            return true;
        }
    }
    return false;
} 

// addPassingHand
// Input: index of chopsticks card and its pointer.
// Purpose: insert the chopstick card back to the passing hand after being used
void Player::addPassingHand(Card *c, int index) {
    hand->insert(index, c);
}