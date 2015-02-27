// file:			main.cpp
// author:			Dan Stueve
// date:			2/7/2015
// last modified:	2/23/2015

// This file contains the main program that runs the chess game

#include <iostream>
#include <string>
#include "board.h"
using std::string;

string intToBin(U64 n)
{
	string result;
	for (int i = 0; i < 64; i++)
	{
		if (n % 2 == 0)
			result.insert(0,"0");
		else
			result.insert(0,"1");
		n = n >> 1;
	}
	return result;
}

// outputs an 8 * 8 representation of a bitboard
void output(U64 n)
{
	string str = intToBin(n);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			std::cout << str[j + i * 8];
		std::cout << '\n';
	}
}


int main()
{

	Board b;
	b.setInitialPosition();

	std::cout << "White Pawns: " << b.getWPawns() << '\n';
	output(b.getWPawns());
	std::cout << std::endl;
	std::cout << "White Knights: " << b.getWKnights() << '\n';
	output(b.getWKnights());
	std::cout << std::endl;
	std::cout << "White Bishops: " << b.getWBishops() << '\n';
	output(b.getWBishops());
	std::cout << std::endl;
	std::cout << "White Rooks: " << b.getWRooks() << '\n';
	output(b.getWRooks());
	std::cout << std::endl;
	std::cout << "White Queens: " << b.getWQueens() << '\n';
	output(b.getWQueens());
	std::cout << std::endl;
	std::cout << "White Kings: " << b.getWKings() << '\n';
	output(b.getWKings());
	std::cout << std::endl;

	std::cout << "Black Pawns: " << b.getBPawns() << '\n';
	output(b.getBPawns());
	std::cout << std::endl;
	std::cout << "Black Knights: " << b.getBKnights() << '\n';
	output(b.getBKnights());
	std::cout << std::endl;
	std::cout << "Black Bishops: " << b.getBBishops() << '\n';
	output(b.getBBishops());
	std::cout << std::endl;
	std::cout << "Black Rooks: " << b.getBRooks() << '\n';
	output(b.getBRooks());
	std::cout << std::endl;
	std::cout << "Black Queens: " << b.getBQueens() << '\n';
	output(b.getBQueens());
	std::cout << std::endl;
	std::cout << "Black Kings: " << b.getBKings() << '\n';
	output(b.getBKings());
	std::cout << std::endl;

	std::cout << "White Pieces: " << b.getWPieces() << '\n';
	output(b.getWPieces());
	std::cout << std::endl;
	std::cout << "Black Pieces: " << b.getBPieces() << '\n';
	output(b.getBPieces());
	std::cout << std::endl;
	std::cout << "All Pieces: " << b.getAllPieces() << '\n';
	output(b.getAllPieces());
	std::cout << std::endl;
	
	std::cin.ignore();
	return 0;
}