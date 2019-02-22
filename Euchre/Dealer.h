#pragma once
#include "Hand.h"
#include "CanUseDeck.h"
class Dealer: public CanUseDeck, public Hand
{
public:
	Dealer();
	Dealer(const Dealer& _dealer);
	Dealer(Deck* _deck,int _player, bool _isdealer = false);
	~Dealer();
	//CanUseDeck Virtual methods
	virtual void DealCards(Hand& _hand, int _cardstodeal);
	virtual void ShuffleDeck();
	virtual Card& TopCardCopy();
	virtual void FreeDeckCardsMemory();
	virtual void FreeDeckMemory();
	virtual void DisplayDeck() const;
	//bool functions
	bool TrumpThreshold(Card::suitType _trump);
	//CardSuit functions
	Card::suitType FavoredSuit();
private:
	int m_SpadesTrump();
	int m_DiamondsTrump();
	int m_HeartsTrump();
	int m_ClubsTrump();
	
};

