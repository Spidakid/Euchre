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
	void DisplayTrumpSuitCopy(bool _showrank) const;
	void DisplayAllHands() const;
	void DisplayCurPlayerHand(int _num);
	
	void ChoosingTrump();
	void ResetCardCheck();
	void SameSuitPlay();
	void TrumpCardPlay();
	void LeftBowerPlay();
	void AnyCardPlay();
	void EndOfRoundPlay();
	void DisplayLeadingCard();
	void DisplayFirstCard();
	//<---returns---->
	int MinNumberConstraint(int _num, const int _min, const int _max);
	int SetPlayerNumber(int* _arrnum); 
private:
	const int MAX_PLAYERS = 4;
	Dealer m_playersArray[4];
	unsigned short int m_dealerchoice;
	int m_dealerIndex;
	Card* m_Trumpcard;
	Card m_TrumpCardCopy;
	Card* m_leadingCard;
	Card m_firstCard;
	int m_leadingCardOwner;
	bool m_wasCardPlayed;
};

