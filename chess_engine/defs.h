#ifndef DEFS_H
#define DEFS_H


// defines the size of the move history array
#define MAXMOVES 2048

/*
We'll be using an unsigned 64-bit integer (Referred to as U64 throughout
the code) for many different aspects of board representation. Because there
are 64 squares on a chess board, a U64 acts as a sort of incidence matrix
for piece existence on the board.
*/
typedef unsigned long long U64;

// enum the squares to their respective value
// A1 = 0 ... H8 = 63
enum SQUARE_ENUM
{
	A1, B1, C1, D1, E1, F1, G1, H1,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A8, B8, C8, D8, E8, F8, G8, H8
};

// enum BLACK to 0/false, WHITE to 1/true
enum
{
	BLACK, WHITE
};

// structure for holding all of the moves played in the game
struct MOVE_HISTORY
{
	int move;
	bool w_king_castle;
	bool w_queen_castle;
	bool b_king_castle;
	bool b_queen_castle;
	int ep_square;
	U64 position_key;
};


/******************** BITBOARD.CPP FUNCTIONS **************/
int countSetBits(U64 bitboard);
int popFirstSetBit(U64 *bitboard);
#endif