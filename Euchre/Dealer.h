#pragma once
#include "Hand.h"
#include "CanUseDeck.h"
class Dealer: public CanUseDeck, public Hand
{
public:
	Dealer();
	Dealer(Deck* _deck,int _player, bool _isdealer = false);
	~Dealer();
	//CanUseDeck Virtual methods
	virtual void DealCards(Hand& _hand, int _cardstodeal);
	virtual void ShuffleDeck();
	virtual Card TopCardCopy();
	virtual void FreeDeckCardsMemory();
	virtual void FreeDeckMemory();
	virtual void DisplayDeck() const;
};

