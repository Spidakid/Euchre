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
	void DisplayCurPlayerHand(int _num);
	int MinNumberConstraint(int _num,const int _min, const int _max);
	void ChoosingTrump();
	//<---returns---->
	int SetPlayerNumber(int* _arrnum);  
private:
	const int MAX_PLAYERS = 4;
	Dealer m_playersArray[4];
	unsigned short int m_dealerchoice;
	int m_dealerIndex;
	Card* m_Trumpcard;
};

