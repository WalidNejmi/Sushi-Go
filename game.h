/*
 * game.h
 * COMP11 Sushi Go
 */

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <fstream>
#include <string>
#include "termfuncs.h"
#include "board.h"
#include "player.h"
#include "vector.h"
using namespace std;

class Game{
    public:
        //constructor/destructor
        Game(string filename, string play_chopsticks);
        ~Game();

        //main gameplay
        void playGame();
        void swapPassingHands(Player &p1, Player &p2, Player &p3);
        void rankMaki();
        void rankPudding();
        void assignMakiPoints();
        void resetRound();
        void assignPuddingPoints();
        int rankScore();
        void handleDifferentCountCaseP();
        void handleDifferentCountCaseM();
        int handleDifferentScoreCase();
        void assignPointersValues();
        void dealCards();
        bool selectAndPassCards();
        bool playOneRound(int round);
        bool checkTie();
        int caseA();
        int caseB();
        int caseC();
        Card *findChopsticks(Player player);
        bool findChopsticksB(Player player);
        void checkChopsticks();
        void addSelectedCards();
        string playWithChop(Card *card);
        bool validSelection(int *c2, int c, int player);
        void eraseCards(int player, int card_index, int *card_index_2);
        int getPlayerIndex(int player);
        void selectCard(int player, int card_index, bool &playingChopsticks, 
        int *card_index_2);
        void getSecondCardIndex(int *card_index_2);
        void error(int player, int c);
    private:
        //constants
        static const int PLAYER_COUNT = 3;
        static const int ROUNDS = 3;
        static const int CARD_HAND = 9;

        //chopsticks activated true/false
        bool play_chopsticks;
        void read_file(string filename);

        //card deck
        Vector deck; // was not a pointer
        //game objects
        Board board;
        Player players[PLAYER_COUNT];
        Player *firstMost;
        Player *secondMost;
        Player *thirdMost;      
};

#endif
