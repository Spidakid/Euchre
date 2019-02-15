#pragma once
#include "Dealer.h"
class Game
{
public:
	Game();
	~Game();
	void Play();
	//<----voids----->
	void InitPlayers(Deck& _deck);
	void SetDealerIndex();
	void StartingDeal();
	void AssignPlayersOrder(Dealer& _player);
	void FreeAllMemoryOnHeap();
	void DisplayTrumpSuit(bool _showrank) const;
	void DisplayAllHands() const;
	//<---returns---->
	int SetPlayerNumber(int* _arrnum);  
private:
	const int MAX_PLAYERS = 4;
	Dealer m_playersArray[4];
	int m_input;
	int m_dealerIndex;
	Card m_Trumpsuit;
};

