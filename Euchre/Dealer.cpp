#include "pch.h"
#include "Dealer.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
Dealer::Dealer() {

}
Dealer::Dealer(Deck* _deck,int _player, bool _isdealer) : Hand(_player, _isdealer), CanUseDeck(_deck,_isdealer)
{
	
}
Dealer::Dealer(const Dealer& _dealer) :Hand(_dealer){
}
Dealer::~Dealer()
{
}
void Dealer::DealCards(Hand& _hand, int _cardstodeal) {
	if (isDealer) {
		for (int i = 0; i < _cardstodeal; i++) {
			_hand.AddCard(deck->Deal());
		}
	}
}
void Dealer::ShuffleDeck() {
	if (isDealer) {
		std::srand(unsigned(time(0)));
		std::random_shuffle(deck->GetDeck().begin(), deck->GetDeck().end());
	}
}
void Dealer::FreeDeckCardsMemory() {
	deck->FreeCardsMemory();
}
void Dealer::FreeDeckMemory() {
	delete deck;
	deck = 0;
}
void Dealer::DisplayDeck() const {
	deck->DisplayDeck();
}
Card& Dealer::TopCardCopy() {
	return *deck->GetDeck().front();
}
bool Dealer::TrumpThreshold(Card::suitType _trump) {
	int threshold = 0;
	std::srand(unsigned(time(0)));
	switch (_trump) {
	case Card::DIAMONDS:
		threshold = m_DiamondsTrump();
		break;
	case Card::CLUBS:
		threshold = m_ClubsTrump();
		break;
	case Card::HEARTS:
		threshold = m_HeartsTrump();
		break;
	case Card::SPADES:
		threshold = m_SpadesTrump();
		break;
	}
	if (threshold == 5) {
		if (rand() % 2 == 1) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (threshold > 5) {
		return true;
	}
	return false;
}
int Dealer::m_SpadesTrump() {
	int threshold = 0;
	for (size_t i = 0; i < hand.size(); i++)
	{
		switch (hand[i]->GetSuit()) {
		case Card::SPADES:
			threshold += 2;
			break;
		case Card::CLUBS:
			threshold += 1;
			break;
		default:
			break;
		}
	}
	return threshold;
}
int Dealer::m_HeartsTrump() {
	int threshold = 0;
	for (size_t i = 0; i < hand.size(); i++)
	{
		switch (hand[i]->GetSuit()) {
		case Card::HEARTS:
			threshold += 2;
			break;
		case Card::DIAMONDS:
			threshold += 1;
			break;
		default:
			break;
		}
	}
	return threshold;
}
int Dealer::m_DiamondsTrump() {
	int threshold = 0;
	for (size_t i = 0; i < hand.size(); i++)
	{
		switch (hand[i]->GetSuit()) {
		case Card::DIAMONDS:
			threshold += 2;
			break;
		case Card::HEARTS:
			threshold += 1;
			break;
		default:
			break;
		}
	}
	return threshold;
}
int Dealer::m_ClubsTrump() {
	int threshold = 0;
	for (size_t i = 0; i < hand.size(); i++)
	{
		switch (hand[i]->GetSuit()) {
		case Card::CLUBS:
			threshold += 2;
			break;
		case Card::SPADES:
			threshold += 1;
			break;
		default:
			break;
		}
	}
	return threshold;
}
Card::suitType Dealer::FavoredSuit() {
	int threshhold = m_SpadesTrump();
	Card::suitType suit = Card::SPADES;

	if (threshhold < m_DiamondsTrump()) {
		threshhold = m_DiamondsTrump();
		suit = Card::DIAMONDS;
	}
	if (threshhold < m_HeartsTrump()) {
		threshhold = m_HeartsTrump();
		suit = Card::HEARTS;
	}
	if (threshhold < m_ClubsTrump()) {
		threshhold = m_ClubsTrump();
		suit = Card::CLUBS;
	}
	return suit;
}
