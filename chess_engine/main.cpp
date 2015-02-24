// file:			main.cpp
// author:			Dan Stueve
// date:			2/7/2015
// last modified:	2/23/2015

// This file contains the main program that runs the chess game

#include <iostream>
#include "board.h"

int main()
{
	Board b;
	b.setInitialPosition();
	
	std::cout << "White Pawns: " << b.getWPawns() << std::endl;
	std::cout << "White Knights: " << b.getWKnights() << std::endl;
	std::cout << "White Bishops: " << b.getWBishops() << std::endl;
	std::cout << "White Rooks: " << b.getWRooks() << std::endl;
	std::cout << "White Queens: " << b.getWQueens() << std::endl;
	std::cout << "White Kings: " << b.getWKings() << std::endl;

	std::cout << "Black Pawns: " << b.getBPawns() << std::endl;
	std::cout << "Black Knights: " << b.getBKnights() << std::endl;
	std::cout << "Black Bishops: " << b.getBBishops() << std::endl;
	std::cout << "Black Rooks: " << b.getBRooks() << std::endl;
	std::cout << "Black Queens: " << b.getBQueens() << std::endl;
	std::cout << "Black Kings: " << b.getBKings() << std::endl;

	std::cout << "White Pieces: " << b.getWPieces() << std::endl;
	std::cout << "Black Pieces: " << b.getBPieces() << std::endl;
	std::cout << "All Pieces: " << b.getAllPieces() << std::endl;
	
	std::cin.ignore();
	return 0;
}