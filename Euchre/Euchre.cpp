// Euchre.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Game.h"
//heaps: cards,deck,& hand container of cards
int main()
{
	//Dealer card;
	Game game;
	game.Play();
	std::cout << "Card instances: "<<Card::instances<<std::endl;
	std::cin.get();
	return 0;
}

