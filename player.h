/* vector.h 
 *
 * Richard Townsend   4/2/20
 *
 * Define the Vector class type and the type name that will be used to refer to
 * the Data in a Vector (using a typedef). Here, I've defined a Vector that
 * will hold Card pointers.
 *
 */
#ifndef PLAYER_H
#define PLAYER_H


#include <iostream>
#include <string>
#include "vector.h"
using namespace std;


class Player {
public:
  Player(); // Constructor
  ~Player();  // Destructor
  
  // Getters
  Data getSelectedCard();
  Data getTemp();
  Data getTemp2();
  Vector *getPassingHand(); 
  Vector *getRevealedCards();
  int getMakiCount();
  int getTempuraCount();
  int getSashimiCount();
  int getDumplingCount();
  int getNigiriCount();
  int getSalmonCount();
  int getEggCount();
  int getSquidCount();
  int getWasabiCount();
  int getPuddingCount();
  int getScore();
  
  int getMakiScore();
  int getTempuraScore();
  int getSashimiScore();
  int getDumplingScore();
  int getNigiriScore();
  int getWasabiScore();
  int getPuddingScore();
  bool getChopstick();
  Vector getSelectedCards();
  void setChopstickF();

  // Setters
  void setSelectedCard(Data c);
  void SetTemp(Card *c);
  void SetTemp2(Card *c);
  void setPassingH(Vector *h);
  void setMakiCount();
  void setTempuraCount();
  void setSashimiCount();
  void setDumplingCount();
  void setNigiriCount();
  void setWasabiCount();
  void setPuddingCount();
  void setScore();
  void setChopstick();

  // Score methods
  void countMaki();
  void scoreTempura();
  void scoreSashimi();
  void scoreDumpling();
  void scoreNigiri();
  void eggWasabi(int i);
  void salmonWasabi(int i);
  void squidWasabi(int i);

  // Others
  void erasePassingCard(int index);
  void eraseSelectedCard(int index);
  void AddSelectedCards(Card *card);
  void addMakiPoints(int points);
  void addPuddingPoints(int points);
  void resetPlayer();
  void insertPassingCard(int index, Card *c);
  int findChopsticks();
  Card *findChopsticksP();
  bool findChopsticksB();
  void addPassingHand(Card *c, int index);

private:
  Vector *hand;
  Vector selected_cards;
  Data temp_selec;
  Data temp_selec_2;
  Card *selected_card;
  Card *selected_card_2;
  // Count
  int number_maki = 0;
  int tempura_count = 0;
  int sashimi_count = 0;
  int dumpling_count = 0;
  int nigiri_count = 0; 
  int n_salmon = 0;
  int n_egg = 0;
  int n_squid = 0;
  int wasabi_count = 0;
  int pudding_count = 0;
  
  // Scores
  int maki_score = 0;
  int tempura_score = 0;
  int sashimi_score = 0;
  int dumpling_score = 0;
  int nigiri_score = 0; 
  int wasabi_score = 0;
  int pudding_score = 0;
  int round_score = 0;
  int total_score = 0;

  bool chopstick = false;
};

#endif