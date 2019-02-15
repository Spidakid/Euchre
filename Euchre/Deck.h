#pragma once
#include "Card.h"
#include <vector>
class Deck
{
public:
	Deck();
	Deck(const Deck& _deck);
	~Deck();
	Card* Deal();
	std::vector<Card*>& GetDeck();
	void FreeCardsMemory();
	void DisplayDeck() const;
private:
	void SetUpDeck();//*Heap Cards
	Card::suitRank GetCardRank(int _num);
	std::vector<Card*> pile;
};


