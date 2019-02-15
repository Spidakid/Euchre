#include "pch.h"
#include "CanUseDeck.h"
CanUseDeck::CanUseDeck() {

}
CanUseDeck::CanUseDeck(Deck* _deck,bool _isdealer)
{
	if (_isdealer) {
		deck = _deck;
	}
	
}
CanUseDeck::CanUseDeck(const CanUseDeck& _can) {
	
}
CanUseDeck::~CanUseDeck()
{	
}
