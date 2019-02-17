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
	Hand::s_turn = MinNumberConstraint(m_playersArray[m_dealerIndex].GetPlayerNumber()+1,1,MAX_PLAYERS);
	//Shuffle Deck
	m_playersArray[m_dealerIndex].ShuffleDeck();
	
	std::cout << "\t\t\t-----Player " << m_dealerIndex +1<< " is shuffling deck!-----"<< std::endl;
	//Deal cards clockwise from dealer
	StartingDeal();	
	//Assigns the top card to be a trump card 
	m_Trumpcard = &m_playersArray[m_dealerIndex].TopCardCopy();

	//Choosing the Trump Card
	ChoosingTrump();
	DisplayCurPlayerHand(MinNumberConstraint(m_dealerIndex + 2,1,MAX_PLAYERS));
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
	std::cout << "The Trump is:\n";
	if (_showrank) {
		std::cout << "\tRank: ";
		m_Trumpcard->DisplayRank();
		std::cout << "; ";
	}
	else {
		std::cout << "\t";
	}
	std::cout << "Suit: ";
	m_Trumpcard->DisplaySuit();
	std::cout << std::endl;
}
//Displays all player hands
void Game::DisplayAllHands() const {
	for (size_t i = 0; i < MAX_PLAYERS;i++) {
		m_playersArray[m_playersArray[i].GetPlayerNumber() - 1].DisplayHand();
	}
}
int Game::MinNumberConstraint(int _num, const int _min, const int _max) {
	if (_num < _min || _num >_max) {
		return _num = _min;
	}
	return _num;
}
void Game::DisplayCurPlayerHand(int _playernum) {
	m_playersArray[MinNumberConstraint(_playernum - 1, 0, MAX_PLAYERS - 1)].DisplayHand();
}
void Game::ChoosingTrump() {
	for (size_t i = 0; i < MAX_PLAYERS; i++)
	{
		DisplayCurPlayerHand(Hand::s_turn);
		DisplayTrumpSuit(true);
		std::cout << "Player " << Hand::s_turn << ", Would you like this to be the Trump?(1=Yes,2=No) ";
		std::cin >> m_input;
		if (m_input == 1) {
			std::cout << "\n\t\t\t-----Player " << Hand::s_turn << " confirmed the Trump-----\n";
			DisplayTrumpSuit(true);
			break;
		}
		Hand::s_turn = MinNumberConstraint(++Hand::s_turn, 1, MAX_PLAYERS);
	}
	if (m_input == 2) {
		std::cout << "The Dealer Team <--Team " << m_playersArray[m_dealerIndex].Team << "--> has confirmed the Trump:" << std::endl;
		DisplayTrumpSuit(false);
	}
}
