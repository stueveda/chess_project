// file:			board.cpp
// author:			Dan Stueve
// date:			2/7/2015
// last modified:	2/23/2015

// this file contains the implementation of the Board class
#include <iostream>
#include "board.h"


/**************** GET WHITE OPERATIONS *************/
U64 Board::getWPawns()
{
	return w_pawns;
}

U64 Board::getWKnights()
{
	return w_knights;
}

U64 Board::getWBishops()
{
	return w_bishops;
}

U64 Board::getWRooks()
{
	return w_rooks;
}
		
U64 Board::getWQueens()
{
	return w_queens;
}

U64 Board::getWKings()
{
	return w_kings;
}

/**************** GET BLACK OPERATIONS ***************/

U64 Board::getBPawns()
{
	return b_pawns;
}

U64 Board::getBKnights()
{
	return b_knights;
}

U64 Board::getBBishops()
{
	return b_bishops;
}

U64 Board::getBRooks()
{
	return b_rooks;
}
		
U64 Board::getBQueens()
{
	return b_queens;
}

U64 Board::getBKings()
{
	return b_kings;
}

/****************** GET GENERAL OPERATIONS ******************/

/*
Returns the U64 representing placement of all white pieces by performing
a bitwise OR on all of the individual white piece U64s
*/
U64 Board::getWPieces()
{
	return w_pawns | w_knights | w_bishops | w_rooks | w_queens | w_kings;
}

/*
Returns the U64 representing placement of all black pieces by performing
a bitwise OR on all of the individual black piece U64s
*/
U64 Board::getBPieces()
{
	return b_pawns | b_knights | b_bishops | b_rooks | b_queens | b_kings;
}

/*
Returns the U64 representing placement of all pieces by performing
a bitwise OR on all white and black pieces
*/
U64 Board::getAllPieces()
{
	return getWPieces() | getBPieces();
}

/****************** SET WHITE OPERATIONS *******************/

void Board::setWPawns(U64 n)
{
	w_pawns = n;
}

void Board::setWKnights(U64 n)
{
	w_knights = n;
}

void Board::setWBishops(U64 n)
{
	w_bishops = n;
}

void Board::setWRooks(U64 n)
{
	w_rooks = n;
}
		
void Board::setWQueens(U64 n)
{
	w_queens = n;
}

void Board::setWKings(U64 n)
{
	w_kings = n;
}

/**************** SET BLACK OPERATIONS ***************/

void Board::setBPawns(U64 n)
{
	b_pawns = n;
}

void Board::setBKnights(U64 n)
{
	b_knights = n;
}

void Board::setBBishops(U64 n)
{
	b_bishops = n;
}

void Board::setBRooks(U64 n)
{
	b_rooks = n;
}
		
void Board::setBQueens(U64 n)
{
	b_queens = n;
}

void Board::setBKings(U64 n)
{
	b_kings = n;
}

/************ SET GENERAL OPERATIONS ***********/

/*
A useful function to set up the initial position of the board.
*/
void Board::setInitialPosition()
{
	// 2^8 + 2^9 + 2^10 + 2^11 + 2^12 + 2^13 + 2^14 + 2^15
	setWPawns(0x000000000000FF00);
	// 2^1 + 2^6
	setWKnights(0x0000000000000042);
	// 2^2 + 2^5
	setWBishops(0x0000000000000024);
	// 2^0 + 2^7
	setWRooks(0x0000000000000081);
	// 2^3
	setWQueens(0x0000000000000008);
	// 2^4
	setWKings(0x0000000000000010);

	// 2^48 + 2^49 + 2^50 + 2^51 + 2^52 + 2^53 + 2^54 + 2^55
	setBPawns(0x00FF000000000000);
	// 2^57 + 2^62
	setBKnights(0x4200000000000000);
	// 2^58 + 2^61
	setBBishops(0x2400000000000000);
	// 2^56 + 2^63
	setBRooks(0x8100000000000000);
	// 2^59
	setBQueens(0x0800000000000000);
	// 2^60
	setBKings(0x1000000000000000);
}

/************* OUTPUT OPERATIONS ****************/

void Board::print(U64 n)
{
	// Implement later - plan to have it output an 8x8 board-looking matrix
}