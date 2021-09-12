/*
Alok Shah, ashah, alokkshah@comcast.net
Deck.h, Assignment #7: Why don't you pass the time
by playing a little solitaire?
*/

#ifndef DECK__H
#define DECK__H

#include <iostream>
#include <vector>
#include <list>

/*Holds Deck values 1-28
  and generates keystream values
  based on the values in deck
  and can encode or decipher
  strings
 */
class Deck{
 public:
  //Constuctor based on string input
  Deck(std::string);
  //Overloaded constructor for char []
  Deck(char []);
  //Finds JOKER1 and swaps with next val
  void stepOne();
  /*Finds JOKER2 and swaps with next two
  vals one after the other
  */
  void stepTwo();
  /*puts cards before 1st joker in deck
    below 2nd joker and puts cards
    under 2nd joker above first
  */
  void stepThree();
  /*moves vals from top of deck to just above the
    last val. Number of values moved corresponds to
    the value of the last val
    uses VecsToDeck()
  */
  void stepFour();
  /*Takes first val and adds the
    val at the position of (firstval+1)
    or first val in this case since indexes start
    at 0, and adds the found value to keystream
    uses VecsToDeck
  */
  void stepFive();
  //generates keystream values using steps 1-5
  void makeKeystream(std::string);
  /*adds keystream values to the
    letters in message to encode it
  */
  void encode(std::string&);
  /*subtracts keystream values to the
    letters in message to decode it
  */
  void decipher(std::string&);
  //performs mod operation in a way that works for -numbers
  char modLetter(char);
  //prints contents of deck for debugging purposes
  void printDeck();
  //prints keystream values for debugging purposes
  void printKeystream();
  //puts the contents of 3 vectors into deck, helper: step3 and step4
  void VecsToDeck(std::vector<int>, std::vector<int>, std::vector<int>);
  //returns deck
  std::list<int> getDeck() {return deck;}
  //returns decksize
  int getDeckSize() {return deck.size();}
  //returns if deck was given 28 unique numbers
  bool isValidDeck();

 private:
  //holds "card" values
  std::list<int> deck;
  //holds keystream values
  std::vector<int> keystream;
  //value of 1st Joker
  static const int JOKER1 = 27;
  //value of 2nd Joker
  static const int JOKER2 = 28;
  //length of the alphabet for char manipulation
  static const int ALPHA_LEN = 26;
};

#endif