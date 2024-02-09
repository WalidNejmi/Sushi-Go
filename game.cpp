/*
 * game.cpp
 * CS11 Sushi Go
 * Edited by: Walid Nejmi, wnejmi01
 */

#include "game.h"
#include "vector.h"

//constructor
Game::Game(string filename, string play_chopsticks){
    //include chopsticks or not
    if(play_chopsticks == "true"){
        this->play_chopsticks = true;
    }else{
        this->play_chopsticks = false;
    }  
    read_file(filename);
    assignPointersValues();
}

// Function to play the entire game
void Game::playGame() {
    string play_on;
    bool q = false;
    for (int round = 0; round < ROUNDS; round++) {
        q = playOneRound(round);
        if (!q) {
            break;  // Break out of the loop if playOneRound returns false
        }
    }
    assignPuddingPoints();
    board.drawWinner(players, rankScore());
}

// assignPointersValues
// Purpose: assign values to pointers used to compare different things
void Game::assignPointersValues() {
    firstMost = &players[0];
    secondMost = &players[1];
    thirdMost = &players[2];     
}
// read_file
// Input: String representing the filename of the deck file to be read.
// Purpose: Reads card information from the specified file and populates 
// the 'deck' vector.
// Output: Void
void Game::read_file(string filename) {
    // Open the file with the given filename
    ifstream file(filename);
    
    // Check if the file opening failed
    if (file.fail()) {
        cerr << "Failed to open deck file: " << filename << endl;
        exit(EXIT_FAILURE);
    }

    string card_name = " ";
    int maki_count = 0;
    // Read the first two strings in the file to get rid of Type and Count
    file >> card_name >> card_name;
    // Read card information from the file
    while (file >> card_name) {
        if (card_name == "Maki") {
            file >> maki_count;
            deck.push_back(new Card(card_name, maki_count));
            maki_count = 0;  // Reset Maki count for the next card
        } else if (card_name == "Chopsticks") {
            if (play_chopsticks) {
                deck.push_back(new Card(card_name, maki_count));
            } else {
                continue;  // Skip to the next iteration of the loop
            }
        } else {
            // For other cards, add a new Card to the deck
            deck.push_back(new Card(card_name, maki_count));
        }
    }
    file.close(); // Close the file after reading
}

// dealCards
// Purpose: deal cards to each player from the deck
void Game::dealCards() {
    for (int i = 0; i < CARD_HAND; i++) {
        for (int j = 0; j < PLAYER_COUNT; j++) {
            Card *dealt_card = deck.back();
            players[j].getPassingHand()->push_back(dealt_card);
            deck.pop_back();
        }
    }
}

// selectAndPassCards
// Function to select and pass cards for each player
bool Game::selectAndPassCards() {
    string response = " ";
    int card_index_2;
    bool playing_chopsticks = false;
    for (int card = 0; card < CARD_HAND; card++) {
        for (int player = 0; player < PLAYER_COUNT; player++) {
            board.drawBoard(players, player);
            int card_index = getPlayerIndex(player);
            if (card_index == - 1) { // Check if cin is an integer
                cerr << " INVALID INPUT: No game for you!" << endl;
                return false;
            }
            selectCard(player, card_index, playing_chopsticks, &card_index_2);
            if (playing_chopsticks) {
                eraseCards(player, card_index, &card_index_2);
                playing_chopsticks = false;
            } else {
                players[player].erasePassingCard(card_index - 1);
            }
        }
        addSelectedCards();
        // Pass deck to the right
        swapPassingHands(players[0], players[1], players[2]);
    }
    return true;
}

// getPlayerIndex
// Input: int player index.
// Purpose: Get the player's card index selection and validate it.
// Output: Returns the selected card index if valid; otherwise, returns -1.
int Game::getPlayerIndex(int player) {
    int cardIndex = 0;
    cout << " Player " << player + 1 << ", select a card: ";
    cin >> cardIndex;

    // Check if cin is an integer
    if (cin.fail()) {
        return -1;
    }

    // Validate user input to ensure it's within the correct range
    while (cardIndex < 1 || 
    cardIndex > players[player].getPassingHand()->size()) {
        cout << "     Please enter a valid number between 1 and ";
        cout << players[player].getPassingHand()->size() << ": ";
        cin >> cardIndex;
    }
    return cardIndex;
}

// selectCard
// Input: player index, index of first selected card, the index of the selected 
// card, adress of boolean indicating whether Chopsticks are in play, 
// pointer to the index of the second selected card.
// Purpose: Handle the player's card selection and depending on whether
// the user has a Chopstick in their selected cards or not.
// Output: Void.
void Game::selectCard(int player, int card_index, bool &playingChopsticks, 
int *card_index_2) {
    string response = " ";
    Card *selected_card = nullptr;
    Card *selected_card_2 = nullptr;
    selected_card = players[player].getPassingHand()->at(card_index - 1);
    players[player].SetTemp(selected_card);

    // If the last card of the player's hand is a chopsticks, don't do
    // prompt the user 
    if (players[player].getPassingHand()->size() == 1) {
        players[player].setChopstickF();
    }
    if (players[player].getChopstick()) { // Check if player has a chopsticks
        response = playWithChop(selected_card);
    }
    // Check whether the selected card is a Chopsticks
    if (selected_card->getSushiType() == "Chopsticks" ) {
        players[player].setChopstick();
    }
    
    if (response == "y") {
        playingChopsticks = true;
        response = " ";
        getSecondCardIndex(card_index_2);
        while (!validSelection(card_index_2, card_index, player)) {
            cin >> *card_index_2;
        }
        selected_card_2 = players[player].getPassingHand()->
        at(*card_index_2 - 1);
        players[player].SetTemp2(selected_card_2);
    }
}

// getSecondCardIndex
// Input: pointer to the index of the second selected card.
// Purpose: Get the index of the second card from the player.
// Output: Void.
void Game::getSecondCardIndex(int *card_index_2) {
    cout << "     Select a second card: ";
    cin >> *card_index_2;
}


// validSelection
// Input: pointer to the index of the second selected card, 
// the index of the first selected card, the player index.
// Purpose: Validate the selection of the second card.
// Output: Returns true if the selection is valid; otherwise, returns false.
bool Game::validSelection(int *c2, int c, int player) {
    // Make sure the input is valid
    if (cin.fail()) {
        cerr << " INVALID INPUT: No game for you!" << endl;
        return false;
    }
    // If the indexes are equal
    if (*c2 == c) {
        cout << "     That card has already been selected." << endl;
        error(player, c);
        return false;
    }

    while(*c2 < 1 
        || *c2 > players[player].getPassingHand()->size()) {
        error(player, c);
        return false;
    }
    return true;
}

// error
// Input: the player index, the index of the selected card.
// Purpose: Display an error message based on the card index and player.
// Output: Void.
void Game::error(int player, int c) {
    if (c == 1) {
        cout << "     Please enter a valid number between 2 and ";
        cout << players[player].getPassingHand()->size() << ": ";
    } else {
        cout << "     Please enter a valid number between 1 and ";
        cout << players[player].getPassingHand()->size() << " (other than ";
        cout << c << "): ";
        }   
}

// addSelectedCards
// Purpose: Add selected cards to the players' selected_cards vector.
// Output: Void.
void Game::addSelectedCards() {
    Card *temp_selec = nullptr;
    Card *temp_selec_2 = nullptr;
    for (int player = 0; player < PLAYER_COUNT; player++) {
        temp_selec = players[player].getTemp();
        players[player].AddSelectedCards(temp_selec);
    }

    for (int player = 0; player < PLAYER_COUNT; player++) {
        if (players[player].getTemp2() != nullptr) {
            temp_selec_2 = players[player].getTemp2();
            players[player].AddSelectedCards(temp_selec_2); 
        }
        players[player].SetTemp2(nullptr); 
    }   
}

// eraseCards
// Input: the player index, the index of the first selected card, 
// pointer to the index of the second selected card.
// Purpose: Erase selected cards from the passing hands, add Chopsticks back, 
// and update the chopstick boolean.
// Output: Void.
void Game::eraseCards(int player, int card_index, int *card_index_2) 
{
    int chop_index = 0;
    int another_chopstick = 0;
    Card *Chopsticks = nullptr;
    if (*card_index_2 < card_index) {
        players[player].erasePassingCard(card_index - 1);
        players[player].erasePassingCard(*card_index_2 - 1);
    } else {
        players[player].erasePassingCard(card_index - 1);
        players[player].erasePassingCard(*card_index_2 - 2);        
    }
    chop_index = players[player].findChopsticks();
    Chopsticks = players[player].findChopsticksP();
    players[player].eraseSelectedCard(chop_index);
    if (*card_index_2 < card_index ) {
        players[player].addPassingHand(Chopsticks, *card_index_2 - 1);
    } else {
        players[player].addPassingHand(Chopsticks, *card_index_2 - 2);        
    }
    players[player].setChopstickF();
    if (players[player].getChopstick()) {
    }

    another_chopstick = players[player].findChopsticks();
    if (another_chopstick != -1) { // Check if the player has another chopstick
        players[player].setChopstick();
    }
    if (players[player].getChopstick()) {
    }    
}
// playWithChop
// Input: Pointer to a card object
// Purpose: Handle the player's choice to play Chopsticks and select 
// a second card.
// Output: Returns the player's response (y/n) to playing with Chopsticks.
string Game::playWithChop(Card *card) {
    string response = " ";
    cout << "     " << card->getSushiType() << " selected!" << endl;
    cout << "     Would you like to use your Chopsticks card to select a";
    cout << " second card from your hand? (y/n): ";
    cin >> response;
    return response;
}

// findChopsticks
// Input: the player whose selected cards are checked for Chopsticks.
// Purpose: Find and return the Chopsticks card in the player's selected cards.
// Output: Returns a pointer to the Chopsticks card if found; otherwise, 
// returns nullptr.
Card *Game::findChopsticks(Player player) {
    for (int i = 0; i < player.getSelectedCards().size(); i++) {
        if (player.getSelectedCards().at(i)->getSushiType() == "Chopsticks") {
            return player.getSelectedCards().at(i);
        }
    }
    return nullptr;
} 


// playOneRound
// Input: the current round number.
// Purpose: Execute one round of the game, including dealing cards, 
// selecting and passing cards, scoring, and handling the continuation 
// of the game.
// Output: Returns true if the player wants to play another round; 
// otherwise, returns false.
bool Game::playOneRound(int round) {
    dealCards();
    if (!selectAndPassCards()) {
        return false;
    }
    string play_on = " ";
    //Set the score of each player;
    for (int i = 0; i < PLAYER_COUNT; i++) {
        players[i].setScore();
    }
    assignMakiPoints();
    board.drawScore(players);
    //Check if the user wants to play another round
    if (round < ROUNDS - 1) {
        cout << " End of round! Ready for Round " << round + 2 << " ? (y/n): ";
        cin >> play_on;
        if (play_on != "y") {
            return false;
        }
    }
    resetRound();
    return true;
}


// swapPassingHands
// Input: References to three Player objects (p1, p2, p3).
// Purpose: Swaps the passing hands between the three players.
//            Each player's passing hand is set to the passing hand 
//            of the next player.
// Output: void
void Game::swapPassingHands(Player &p1, Player &p2, Player &p3) {    
    Vector* temp_hand = p1.getPassingHand();
    Vector* temp_hand_2 = p2.getPassingHand();

    p1.setPassingH(p3.getPassingHand());
    p2.setPassingH(temp_hand);
    p3.setPassingH(temp_hand_2);
}

// resetRound
// Input: None
// Purpose: Resets the game state at the end of each round.
// Output: Void
void Game::resetRound() {
    for (int i = 0; i < PLAYER_COUNT; i++) {
        players[i].resetPlayer();
    }
}

// rankMaki
// Input: None
// Purpose: Ranks players based on their Maki counts and updates firstMost, 
// secondMost, and thirdMost.
// Output: Void
void Game::rankMaki() {
    assignPointersValues();
    if (players[0].getMakiCount() == players[1].getMakiCount()) {
        if (players[2].getMakiCount() > players[0].getMakiCount()) {
            firstMost = &players[2];
            secondMost = &players[1];
            thirdMost = &players[0];
        } else {
            firstMost = &players[1];
            secondMost = &players[0];
            thirdMost = &players[2];
        }      
    } else if (players[0].getMakiCount() == players[2].getMakiCount()) {
        if (players[1].getMakiCount() > players[0].getMakiCount()) {
            firstMost = &players[1];
            secondMost = &players[2];
            thirdMost = &players[0];
        } else {
            firstMost = &players[2];
            secondMost = &players[0];
            thirdMost = &players[1];
        }        
    } else if (players[1].getMakiCount() == players[2].getMakiCount()) {
        if (players[0].getMakiCount() > players[1].getMakiCount()) {
            firstMost = &players[0];
            secondMost = &players[1];
            thirdMost = &players[2];
        } else {
            firstMost = &players[1];
            secondMost = &players[2];
            thirdMost = &players[0];
        }
    } else {
        handleDifferentCountCaseM();
    }
}

// assignMakiPoints
// Input: None
// Purpose: Assigns Maki points to players based on their rankings.
// Output: Void
void Game::assignMakiPoints() {
    // Rank players based on Maki counts
    rankMaki();
    // Check if there is a tie for the most Maki
    if (firstMost->getMakiCount() == secondMost->getMakiCount() &&
        firstMost->getMakiCount() == thirdMost->getMakiCount()) {
        // Handle the tie for the most Maki
        // Split the 2 points evenly among the tied players 
        firstMost->addMakiPoints(2);
        secondMost->addMakiPoints(2);
        thirdMost->addMakiPoints(2);
    } else if (firstMost->getMakiCount() == secondMost->getMakiCount()) {
        // Handle the tie for the most Maki
        // Split the 6 points evenly among the tied players 
        firstMost->addMakiPoints(3);
        secondMost->addMakiPoints(3);
    } else {
        // Assign points to the player with the most Maki
        firstMost->addMakiPoints(6);

        // Check if there is a tie for the second most Maki
        if (secondMost->getMakiCount() == thirdMost->getMakiCount()) {
            // Handle the tie for the second most Maki
            // Split the 3 points evenly among the tied players
            secondMost->addMakiPoints(1);
            thirdMost->addMakiPoints(1);
        } else {
            // Assign points to the player with the second most Maki
            secondMost->addMakiPoints(3);
        }
    }
}


// rankPudding
// Input: None
// Purpose: Ranks players based on their Pudding counts and updates firstMost, 
// secondMost, and thirdMost.
// Output: Void
void Game::rankPudding() {
    assignPointersValues();
    if (players[0].getPuddingCount() == players[1].getPuddingCount()) {
        if (players[2].getPuddingCount() > players[0].getPuddingCount()) {
            firstMost = &players[2];
            secondMost = &players[1];
            thirdMost = &players[0];
        } else {
            firstMost = &players[1];
            secondMost = &players[0];
            thirdMost = &players[2];
        }      
    } else if (players[0].getPuddingCount() == players[2].getPuddingCount()) {
        if (players[1].getPuddingCount() > players[0].getPuddingCount()) {
            firstMost = &players[1];
            secondMost = &players[2];
            thirdMost = &players[0];
        } else {
            firstMost = &players[2];
            secondMost = &players[0];
            thirdMost = &players[1];
        }        
    } else if (players[1].getPuddingCount() == players[2].getPuddingCount()) {
        if (players[0].getPuddingCount() > players[1].getPuddingCount()) {
            firstMost = &players[0];
            secondMost = &players[1];
            thirdMost = &players[2];
        } else {
            firstMost = &players[1];
            secondMost = &players[2];
            thirdMost = &players[0];
        }
    } else {
        handleDifferentCountCaseP();
    }
}

// handleDifferentCountCaseP
// Input: None
// Purpose: Handles the case where players have different Pudding counts.
// Output: Void
void Game::handleDifferentCountCaseP() {
    for (int i = 0; i < PLAYER_COUNT; i++) {
        if (players[i].getPuddingCount() > 
            players[(i + 1) % 3].getPuddingCount() &&
            players[i].getPuddingCount() > 
            players[(i + 2) % 3].getPuddingCount()) {
            firstMost = &players[i];
            if (players[(i + 1) % 3].getPuddingCount() > 
                players[(i + 2) % 3].getPuddingCount()) {
                secondMost = &players[(i + 1) % 3];
                thirdMost = &players[(i + 2) % 3];
            } else {
                secondMost = &players[(i + 2) % 3];
                thirdMost = &players[(i + 1) % 3];
            }
        }
    }
}

// handleDifferentCountCaseM
// Input: None
// Purpose: Handles the case where players have different Maki counts.
// Output: Void
void Game::handleDifferentCountCaseM() {
    for (int i = 0; i < PLAYER_COUNT; i++) {
    if (players[i].getMakiCount() > players[(i + 1) % 3].getMakiCount()
        && players[i].getMakiCount() > players[(i + 2) % 3].getMakiCount()){
        firstMost = &players[i];
        if (players[(i + 1) % 3].getMakiCount() >
            players[(i + 2) % 3].getMakiCount()) {
            secondMost = &players[(i + 1) % 3];
            thirdMost = &players[(i + 2) % 3];
            } else {
                secondMost = &players[(i + 2) % 3];
                thirdMost = &players[(i + 1) % 3];
            }
        }
    }
}

// assignPuddingPoints
// Input: None
// Purpose: Assigns Pudding points to players based on their rankings.
// Output: Void
void Game::assignPuddingPoints() {
    // Rank players based on Pudding counts
    rankPudding();

    if (firstMost ->getPuddingCount() == secondMost->getPuddingCount()
    && firstMost->getPuddingCount() == thirdMost->getPuddingCount()) {
        return;
    }
    // Check if there is a tie for the most Pudding
    else if (firstMost->getPuddingCount() == secondMost->getPuddingCount()) {
        // Handle the tie for the most Pudding
        // Split the 6 points evenly among the tied players 
        firstMost->addPuddingPoints(3);
        secondMost->addPuddingPoints(3);
        thirdMost->addPuddingPoints(-6);
    } else {
        // Assign points to the player with the most Pudding
        firstMost->addPuddingPoints(6);

        // Check if there is a tie for the second most Pudding
        if (secondMost->getPuddingCount() == thirdMost->getPuddingCount()) {
            // Handle the tie for the second most Pudding
            // Split the -6 points evenly among the tied players
            secondMost->addPuddingPoints(-3);
            thirdMost->addPuddingPoints(-3);
        } else {
            // Assign points to the player with the second most Pudding
            thirdMost->addPuddingPoints(-6);
        }
    }
}

// rankScore
// Input: None
// Purpose: Ranks players based on their overall scores and returns 
// the index of the winner.
// Output: Integer representing the index of the winner.
int Game::rankScore() {
    assignPointersValues();
    if (checkTie()) {
        return -1;
    } else if (players[0].getScore() == players[1].getScore()) {
        int i = caseA();
        return i;
    } else if (players[0].getScore() == players[2].getScore()) {
        int i = caseB();
        return i;
    } else if (players[1].getScore() == players[2].getScore()) {
        int i = caseC();
        return i;
    } else {
        int i = handleDifferentScoreCase();
        return i;
    }
    return -1;
}

// caseC
// Input: None
// Purpose: Determine the case where player 2 has the highest score 
// or the highest pudding count in case of a tie.
// Output: Integer representing the index of the winning player (0, 1, or 2).
int Game::caseC() {
    if (players[0].getScore() > players[1].getScore()) {
        return 0;
    } else {
        if (players[1].getPuddingCount() > players[2].getPuddingCount()) {
            return 1;
        } else {
            return 2;
        }
    }
}


// Function: caseB
// Input: None
// Purpose: Determine the case where player 1 has the highest score 
// or the highest pudding count in case of a tie.
// Output: Integer representing the index of the winning player (0, 1, or 2).
int Game::caseB() {
    if (players[1].getScore() > players[0].getScore()) {
        return 1;
    } else {
        if (players[0].getPuddingCount() > players[2].getPuddingCount()) {
            return 0;
        } else {
            return 2;
        }
    }
}


//caseA
//Input: None
// Purpose: Determine the case where player 3 has the highest score 
// or the highest pudding count in case of a tie.
// Output: Integer representing the index of the winning player (0, 1, or 2).
int Game::caseA() {
    if (players[2].getScore() > players[0].getScore()) {
        return 2;
    } else {
        if (players[1].getPuddingCount() > players[0].getPuddingCount()) {
            return 1;
        } else {
            return 0;
        }
    }
}

// checkTie
// Purpose: Check if there 
bool Game::checkTie() {
    if (players[0].getScore() == players[1].getScore()
    && players[0].getScore() == players[2].getScore()) {
        return true;
    }
    return false;
}
// handleDifferentScoreCase
// Input: None
// Purpose: Handles the case where players have different overall scores.
// Output: Integer representing the index of the winner.
int Game::handleDifferentScoreCase() {
    for (int i = 0; i < PLAYER_COUNT; i++) {
        if (players[i].getScore() > players[(i + 1) % 3].getScore()
        &&  players[i].getScore() > players[(i + 2) % 3].getScore()) {
            return i;        
        }
    }
    return -1;
}
//destructor
Game::~Game(){
    for (int i = 0; i < deck.size(); i++) {
        if (deck.at(i) != nullptr) {
            delete deck.at(i);
        }
    }
}

