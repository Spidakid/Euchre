#pragma once
#include "Deck.h"
#include "Hand.h"
class CanUseDeck
{
public:
	CanUseDeck();
	CanUseDeck(Deck* _dealer, bool _isdealer = false);
	CanUseDeck(const CanUseDeck& _can);
	~CanUseDeck();
	virtual void DealCards(Hand& _hand,int _cardstodeal) = 0;
	virtual void ShuffleDeck() = 0;
	virtual Card TopCardCopy() = 0;
	virtual void FreeDeckCardsMemory() = 0;
	virtual void FreeDeckMemory() = 0;
	virtual void DisplayDeck() const = 0;
protected:
	Deck *deck = 0;//*Heap Deck
};

