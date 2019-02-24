#include "pch.h"
#include "Hand.h"
#include <iostream>

Hand::Hand() {

}
Hand::Hand(int _playernumber,bool _isdealer)
{
	isDealer = _isdealer;
	if (_playernumber < 0 || _playernumber > 4) {
		m_player = 1;
	}
	else {
		m_player = _playernumber;
	}
}
int Hand::s_turn = 0;
Hand::Hand(const Hand& _hand) {
	m_player = _hand.m_player;
	Team = _hand.Team;
}
Hand::~Hand()
{
}
void Hand::DisplayHand() const {
	std::cout << "Player "<< m_player<< " Hand:"<<std::endl;
	for (std::vector<Card*>::const_iterator iter = hand.begin();iter !=hand.end();++iter)
	{
		std::cout << "\tRank: ";
		(*iter)->DisplayRank();
		std::cout << "; Suit: ";
		(*iter)->DisplaySuit();
		std::cout << std::endl;
	}
	std::cout << "<--TEAM " << Team << "-->"<<std::endl;
	if (isDealer) {
		std::cout << "*[Dealer]>" << std::endl;
	}
}
//Starting at 1
Card* Hand::PlayCard(int _cardpos,bool _wanttodiscard) {
	if (!hand.empty()) {
		Card* playcard = hand[_cardpos-1];
		if (hand.size() > 1) {
			Card* endcard = hand[hand.size() - 1];
			hand[_cardpos-1] = endcard;
			hand[hand.size() - 1] = playcard;
			
		}
		hand.pop_back();
		if (_wanttodiscard) {
			delete playcard;
			playcard = 0;
			return 0;
		}
		return playcard;
	}
	return 0;
}
std::vector<Card*>& Hand::GetHand() {
	return hand;
}
void Hand::AddCard(Card* _card) {
	hand.push_back(_card);
}
int Hand::GetPlayerNumber() const {
	return m_player;
}
void Hand::FreeHandCardsMemory() {
	for (std::vector<Card*>::iterator iter = hand.begin(); iter != hand.end(); ++iter)
	{
		if (*iter != NULL) {
			delete *iter;
		}
		*iter = 0;
	}
	hand.clear();
}
