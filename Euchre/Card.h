#pragma once
#include <string>
class Card
{
public:
	//enums
	enum suitType { SPADES, HEARTS, CLUBS, DIAMONDS };
	enum suitRank {EIGHT = 1,NINE,TEN,QUEEN,KING,ACE,JACK};
	//structors
	Card();
	Card(suitType _suite,suitRank _rank);
	Card(const Card& _card);
	~Card();
	//function members
	suitRank GetRank() const;
	void DisplayRank() const;
	suitType GetSuit() const;
	void DisplaySuit() const;
	void SetSuit(Card::suitType _type);
	//data members
	static int instances;
private:
	suitType m_suit;
	suitRank m_rank;
};

