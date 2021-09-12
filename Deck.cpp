/*
Alok Shah, ashah, alokkshah@comcast.net
Deck.cpp, Assignment #7: Why don't you pass the time
by playing a little solitaire?
*/

#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include "Deck.h"

//prints an error if the filename is not accessible
Deck::Deck(std::string filename){
  std::ifstream fin(filename.c_str());
  int card = -1;
  if(fin.is_open()){
    while(fin >> card){
      deck.push_back(card);
    }
  } else{
    std::cerr << "ERROR: Deck file could not open or was not found\n";
    exit(1);
  }
  fin.close();
}

//prints an error if the filename is not accessible
Deck::Deck(char filename[]){
  std::ifstream fin(filename);
  int card = -1;
  if(fin.is_open()){
    while(fin >> card){
      deck.push_back(card);
    }
  } else{
    std::cerr << "ERROR: Deck file could not open or was not found\n";
    exit(1);
  }
  fin.close();
}

void Deck::printDeck(){
  std::list<int>::iterator it = deck.begin();
  while(it != deck.end()){
    std::cout << *it << " ";
    it++;
  }
  std::cout << "\n";
}

void Deck::stepOne(){
  if(deck.size() < 2) return;

  std::list<int>::iterator it2 = deck.begin();
  std::list<int>::iterator it1 = it2++;

  while(it1 != deck.end()){
    if(it2 == deck.end()){
      it2 = deck.begin();
    }
    if(*it1 == JOKER1){
        std::swap(*it1, *it2);
        return;
    } else{
      it1 = it2++;
    }
  }
}

void Deck::stepTwo(){
  if(deck.size() < 2) return;

  std::list<int>::iterator it2 = deck.begin();
  std::list<int>::iterator it1 = it2++;

  while(it1 != deck.end()){
    if(it2 == deck.end()){
      it2 = deck.begin();
    }
    if(*it1 == JOKER2){
      if(it2 != deck.end()){
        std::swap(*it1, *it2);
        it1 = it2++;
        if(it2 != deck.end()){
          std::swap(*it1, *it2);
          return;
        } else{
          it2 = deck.begin();
          std::swap(*it1, *it2);
          return;
        }
      }
      return;
    } else{
      it1 = it2++;
    }
  }
}

void Deck::stepThree(){
  std::list<int>::iterator it = deck.begin();

  std::vector<int> top;
  std::vector<int> mid;
  std::vector<int> bot;


  while((*it != JOKER1 && *it != JOKER2) && it != deck.end()){
    top.push_back(*it);
    it++;
  }

  mid.push_back(*it);
  it++;

  while(*it != JOKER1 && *it != JOKER2 && it != deck.end()){
    mid.push_back(*it);
    it++;
  }

  mid.push_back(*it);
  it++;

  while(it != deck.end()){
    bot.push_back(*it);
    it++;
  }
  VecsToDeck(bot, mid, top);
}

void Deck::VecsToDeck(std::vector<int> top, std::vector<int> mid,
                      std::vector<int> bot){
  std::list<int>::iterator it = deck.begin();

  if(deck.size() != top.size() + mid.size() + bot.size()) return;

  for(unsigned i = 0; i < top.size(); i++){
    *it = top[i];
    it++;
  }

  for(unsigned i = 0; i < mid.size(); i++){
    *it = mid[i];
    it++;
  }

  for(unsigned i = 0; i < bot.size(); i++){
    *it = bot[i];
    it++;
  }
}

void Deck::stepFour(){
  int botVal = 0;
  if(botVal == JOKER2){
    botVal = JOKER1; //Joker1 and 2 are both 27 for this step
  } else{
    botVal = deck.back();
  }
  std::list<int>::iterator it = deck.begin();


  std::vector<int> top;
  std::vector<int> mid;
  std::vector<int> bot;

  for(int i = 0; i < botVal; i++){
    top.push_back(*it);
    it++;
  }

  for(unsigned i = botVal; i < deck.size()-1&&it != deck.end(); i++){
    mid.push_back(*it);
    it++;
  }

  bot.push_back(botVal);

  VecsToDeck(mid, top, bot);
}

void Deck::stepFive(){
  int keyLoc = deck.front();
  if(keyLoc == JOKER2){
    keyLoc = JOKER1; //Joker1 and 2 are both 27 for this step
  }
  std::list<int>::iterator it = deck.begin();

  for(int i = 0; i < keyLoc; i++){
    it++;
  }
  if(*it != JOKER1 && *it != JOKER2){
    keystream.push_back(*it);
  }
}

void Deck::makeKeystream(std::string msg){
  while(keystream.size() < msg.size()){
    stepOne();
    stepTwo();
    stepThree();
    stepFour();
    stepFive();
  }
}

void Deck::encode(std::string &msg){
  makeKeystream(msg);
  for(unsigned i = 0; i < msg.size(); i++){
    msg[i] -= 'A';
    msg[i] += keystream[i];
    msg[i] = modLetter(msg[i]);
    msg[i] += 'A';
  }
}

void Deck::decipher(std::string &msg){
  makeKeystream(msg);
  for(unsigned i = 0; i < msg.size(); i++){
    msg[i] -= 'A';
    msg[i] -= keystream[i];
    msg[i] = modLetter(msg[i]);
    msg[i] += 'A';
  }
}


void Deck::printKeystream(){
  for(unsigned i = 0; i < keystream.size(); i++){
    std::cout << keystream[i] << " ";
  }
  std::cout << "\n";
}

char Deck::modLetter(char c){
  return (ALPHA_LEN+(c%ALPHA_LEN)) % ALPHA_LEN; //c%ALPHA_LEN but works for -nums
}

bool Deck::isValidDeck(){
  deck.unique();
  //values 1-28 expected
  if(deck.size() != 28){
    return false;
  }
  std::list<int>::iterator it = deck.begin();
  while(it != deck.end()){
    if(*it < 1 || *it > 28){
      return false;
    }
    it++;
  }
  return true;
}