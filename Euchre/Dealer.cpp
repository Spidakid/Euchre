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
