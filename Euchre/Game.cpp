#include "pch.h"
#include "Game.h"
#include "Deck.h"
#include "Hand.h"
#include "Dealer.h"
#include <iostream>

Game::Game()
{
}
Game::~Game()
{
}
void Game::Play()
{
	Deck *deck = new Deck();
	std::cout << "\t\t\t\t<Welcome to a game of Euchre!>\n\n";
	std::cout << "Which player wants to be dealer?(1-4) ";
	
	std::cin >> m_input;
	//init players
	InitPlayers(*deck); 
	SetDealerIndex();
	//Shuffle Deck
	m_playersArray[m_dealerIndex].ShuffleDeck();
	
	std::cout << "\t\t\t-----Player " << m_dealerIndex +1<< " is shuffling deck!-----"<< std::endl;
	//Deal cards clockwise from dealer
	StartingDeal();	
	//Assigns copy of the top card to be a trump card 
	m_Trumpsuit = m_playersArray[m_dealerIndex].TopCardCopy();

	//Displays Trump Suit
	DisplayTrumpSuit(true);
	//Displays all player hands
	DisplayAllHands();

	//Frees all memory on the heap
	FreeAllMemoryOnHeap();
}
//Initialize Players
void Game::InitPlayers(Deck& _deck) {
	// init Dealer
	Dealer dealer(&_deck,m_input, true);
	int playerNumbers[4];
	playerNumbers[dealer.GetPlayerNumber() - 1] = dealer.GetPlayerNumber();
	m_playersArray[dealer.GetPlayerNumber() - 1] = dealer;
	//Init Players
	Dealer p1(&_deck, SetPlayerNumber(playerNumbers));
	Dealer p2(&_deck, SetPlayerNumber(playerNumbers));
	Dealer p3(&_deck, SetPlayerNumber(playerNumbers));
	AssignPlayersOrder(dealer);
	AssignPlayersOrder(p1);
	AssignPlayersOrder(p2);
	AssignPlayersOrder(p3);
	//Assign Teams
	for (size_t i = 0; i < MAX_PLAYERS; i++) {
		if (i % 2 == 0) {
			m_playersArray[i].Team = 'A';
		}
		else {
			m_playersArray[i].Team = 'B';
		}
	}
	
}
//Set number to player 
int Game::SetPlayerNumber(int* _arrnum) {
	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (i + 1 != _arrnum[i]) {
			_arrnum[i] = i + 1;
			return i + 1;
		}
	}
	return 0;
}
//Place Players into array in order of player number
void Game::AssignPlayersOrder(Dealer& _player) {
	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (i + 1 == _player.GetPlayerNumber()) {
			m_playersArray[i] = _player;
		}
	}
}
//Set the current dealer index to private member
void Game::SetDealerIndex() {
	for (size_t i = 0; i < MAX_PLAYERS; i++)
	{
		if (m_playersArray[i].isDealer) {
			m_dealerIndex = i;
		}
	}
}
//Deal cards clockwise from current dealer & place cards in players hands
void Game::StartingDeal() {
	int index = m_dealerIndex +1;
	//First Pass
	while (index != m_dealerIndex)
	{
		if (index > MAX_PLAYERS - 1) {
			index = 0;
		}
		m_playersArray[m_dealerIndex].DealCards(m_playersArray[index], 3);//d3
		index++;//4
		if (index > MAX_PLAYERS - 1) {
			index = 0;
		}
		if (index == m_dealerIndex) {
			m_playersArray[m_dealerIndex].DealCards(m_playersArray[index], 3);
		}
	}

	//Second Pass
	index = m_dealerIndex + 1;
	while (index != m_dealerIndex)
	{
		if (index > MAX_PLAYERS - 1) {
			index = 0;
		}
		m_playersArray[m_dealerIndex].DealCards(m_playersArray[index], 2);
		index++;
		if (index > MAX_PLAYERS - 1) {
			index = 0;
		}
		if (index == m_dealerIndex) {
			m_playersArray[m_dealerIndex].DealCards(m_playersArray[index], 2);
		}
	}
}
//Frees heaps in cards, deck, & hand container holding the cards
void Game::FreeAllMemoryOnHeap() {
	//Free memory on all cards found in the current dealer's deck
	m_playersArray[m_dealerIndex].FreeDeckCardsMemory();

	//Free Memory on all decks regardless if they are already null
	for (size_t i = 0; i < MAX_PLAYERS; i++)
	{
		m_playersArray[i].FreeDeckMemory();
	}
	//Free Memory of cards in all hands
	for (size_t i = 0; i < MAX_PLAYERS; i++)
	{
		m_playersArray[i].FreeHandCardsMemory();
	}
}
//Displays the Trump Card info
void Game::DisplayTrumpSuit(bool _showrank) const{
	if (_showrank) {
		std::cout << "<**Trump Suit**> \n\tRank: ";
		m_Trumpsuit.DisplayRank();
		std::cout << "; ";
	}
	std::cout << "Suit: ";
	m_Trumpsuit.DisplaySuit();
	std::cout << std::endl;
}
//Displays all player hands
void Game::DisplayAllHands() const {
	for (size_t i = 0; i < MAX_PLAYERS;i++) {
		m_playersArray[m_playersArray[i].GetPlayerNumber() - 1].DisplayHand();
	}
}

