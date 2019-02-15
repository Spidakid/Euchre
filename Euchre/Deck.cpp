#include "pch.h"
#include "Deck.h"
#include <iostream>

Deck::Deck()
{
	SetUpDeck();
	//std::cout << "Deck Constructor" << std::endl;
}
Deck::Deck(const Deck& _deck) {
	//std::cout << "Deck Copy Constructor called"<<std::endl;
}
Deck::~Deck()
{
	//std::cout<< "~Deck Destructor"<<std::endl;
}
void Deck::SetUpDeck() {
	typedef unsigned short int ushort;
	const int MAX = 7;

	//Spades
	for (ushort i = 0; i < MAX; i++) {
		pile.push_back(new Card(Card::SPADES, GetCardRank(i)));
	}
	//Hearts
	for (ushort i = 0; i < MAX; i++) {
		pile.push_back(new Card(Card::HEARTS, GetCardRank(i)));
	}
	//Clubs
	for (ushort i = 0; i < MAX; i++) {
		pile.push_back(new Card(Card::CLUBS, GetCardRank(i)));
	}
	//Diamonds
	for (ushort i = 0; i < MAX; i++) {
		pile.push_back(new Card(Card::DIAMONDS, GetCardRank(i)));
	}
}
Card::suitRank Deck::GetCardRank(int _num) {
	switch (_num) {
	case 0:
		return Card::EIGHT;
		break;
	case 1:
		return Card::NINE;
		break;
	case 2:
		return Card::TEN;
		break;
	case 3:
		return Card::JACK;
		break;
	case 4:
		return Card::QUEEN;
		break;
	case 5:
		return Card::KING;
		break;
	case 6:
		return Card::ACE;
		break;
	}
	return Card::ACE;
}
std::vector<Card*>& Deck::GetDeck(){
	return pile;
}
void Deck::FreeCardsMemory() {
	for (std::vector<Card*>::iterator iter = pile.begin(); iter != pile.end();++iter) {
		delete *iter;
		*iter = 0;
	}
	pile.clear();
}
Card* Deck::Deal() {
	if (!pile.empty()) {
		Card* playcard = pile.front();
		if (pile.size() > 1) {
			Card* nextcard = 0;
			for (int i = 0; i < pile.size();i++) {
				if (i != pile.size() - 1) {
					nextcard = pile[i+1];
					pile[i] = nextcard;
				}
			}
		}
		pile.pop_back();
		return playcard;
	}
	return 0;
}
void Deck::DisplayDeck() const{
	std::cout << "Deck: "<<std::endl;
	for (int i = 0; i < pile.size();i++) {
		std::cout << "Rank: "; 
		pile[i]->DisplayRank();
		std::cout << " Suite: ";
		pile[i]->DisplaySuit();
		std::cout<<std::endl;
	}
}
