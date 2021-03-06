#pragma once
#include <vector>
#include "Card.h"
class Hand
{
public:
	//structors
	Hand();
	Hand(int _player,bool _isdealer);
	Hand(const Hand& _hand);
	~Hand();

	//voids
	void DisplayHand() const;
	void AddCard(Card* _card);
	void FreeHandCardsMemory();
	//returns
	Card* PlayCard(int _cardpos,bool _wanttodiscard = false);
	std::vector<Card*>& GetHand();
	int GetPlayerNumber() const;
	
	//static
	static int s_turn;
	//variables
	int tricks;
	bool isDealer;
	char Team;
protected:
	std::vector<Card*> hand;
	int m_player;
};

