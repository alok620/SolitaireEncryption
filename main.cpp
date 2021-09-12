/*
Alok Shah, ashah, alokkshah@comcast.net
main.cpp, Assignment #7: Why don't you pass the time
by playing a little solitaire?
*/

//Deck is a class with a list container for deck values
//and a vector container for keystream values with
//functions to find the keystream values based off of the deck


//working/tested

#include <iostream>
#include <list>
#include <algorithm>
#include <cstring>
#include <string>
#include "Deck.h"

/*formats message to all upper case, removes
  whitespace and punctuation, and adds Xs
  uses addX
*/
void format(std::string &);

//adds Xs to msg until msg.size() is a multiple of 5
void addX(std::string &);

//encodes message
void encrypt(Deck &, std::string &);

//deciphers message
void decrypt(Deck &, std::string &);


int main(int argc, char **argv){

  //Usage error for invalid cmd line params
  if(argc > 3 || argc < 2 || (*argv[1] != 'e' && *argv[1] != 'd')){
    std::cerr << "USAGE: " << argv[0]
              << "(e/d for encode/decipher) deckfilename\n";
    exit(1);
  }

  std::string filename;
  //if no filename given input now
  if(argc == 2){
    std::cout << "Input deckfile name:\n";
    std::getline(std::cin, filename);
  } else{
    filename = argv[2];
  }


  Deck d(filename);

  if(!d.isValidDeck()){
    std::cerr << "ERROR: Deck must have exactly 28 unique"
              << " values 1-28\n";
    exit(1);
  }

  std::string msg;

  //e encrypts d decrypts
  if(*argv[1] == 'e'){

    std::cout << "Enter message to be encrypted (non-letters ignored)\n";
    std::getline(std::cin, msg);
    format(msg);
    std::cout << "Plaintext message is: " << msg << std::endl;
    encrypt(d, msg);

    std::cout << "The encrypted message is: " << msg << std::endl;
  }
  else if(*argv[1] == 'd'){
    std::cout << "Enter message to be decrypted:\n";

    std::getline(std::cin, msg);
    format(msg);
    decrypt(d, msg);

    std::cout << "The decrypted message is: " << msg << std::endl;
  }
}

void format(std::string &msg){
  for(unsigned i = 0; i < msg.size(); i++){
    if(!std::isalpha(msg[i])|| std::ispunct(msg[i])){
      msg.erase(i, 1);
      i--;
    } else{
      msg[i] = std::toupper(msg[i]);
    }
  }
  addX(msg);
}

void addX(std::string &msg){
  while(msg.size() % 5 != 0){
    msg.push_back('X');
  }
}

void encrypt(Deck &d, std::string &msg){
  d.encode(msg);
}

void decrypt(Deck &d, std::string &msg){
  d.decipher(msg);
}