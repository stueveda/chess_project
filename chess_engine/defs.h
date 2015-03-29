#ifndef DEFS_H
#define DEFS_H


// defines the size of the move history array
#define MAXMOVES 2048
#define MAXPOSITIONMOVES 256

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

enum 
{
	NONE,
	wP, wN, wB, wR, wQ, wK,
	bP, bN, bB, bR, bQ, bK
};

struct MOVE
{
	/* bits:
		0 - 6 denote from square						(7 bits)
		7 - 13 denote to square							(7 bits)
		14 - 17 denote type of piece captured			(4 bits)
		18 denotes whether it was an en passant capture	(1 bit)
		19 denotes whether it was a pawn start move		(1 bit)
		20 - 23 denotes what piece a pawn promoted to	(4 bits)
		24 denotes if it was a castle move				(1 bit)
	*/
	int move;
	int value;
};

// define some macros to make extracting data from the move int easier
#define FROMSQ(move) ((move) & 0x7F)
#define TOSQ(move) (((move) >> 7) & 0x7F)
#define CAP_PIECE(move) (((move) >> 14) & 0xF)
#define PROM_PIECE(move) (((move) >> 20) & 0xF)

#define EP_FLAG 0x40000
#define PS_FLAG 0x80000
#define CAS_FLAG 0x1000000

#define M_MOVE(from, to, cap, prom, flag) \
								  ((from) \
								| ((to) << 7) \
								| ((cap) << 14) \
								| ((prom) << 20) \
								| ((flag)))

struct MOVE_LIST
{
	MOVE moves[MAXPOSITIONMOVES];
	int count;
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

/******************** FUNCTIONS.CPP FUNCTIONS **************/
int countBits(U64 bitboard);
int popFirstSetBit(U64 &bitboard);
char *printMove(const int move);
char *printSquare(const int sq);

#endif