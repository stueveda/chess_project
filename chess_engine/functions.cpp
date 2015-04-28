// miscellaneous functions
#include "defs.h"
#include <iostream>

// count the number of 1's in a bitboard
int countBits(U64 bb)
{
	int total = 0;
	for (int i = 0; i < 64; i++)
	{
		if ((bb & 1) == 1)
			total += 1;
		bb = bb >> 1;
	}
	return total;
}


int popFirstSetBit(U64 &bb)
{
	if (bb == 0)
		return -1;

	for (int i = 0; i < 64; i++)
	{
		if ((bb & (1ULL << i)) == (1ULL << i))
		{
			bb = (bb ^ (1ULL << i));
			return i;
		}
	}
}

char *printSquare(const int sq)
{
	static char sqStr[3];
	int file = sq % 8;
	int rank = sq / 8;
	sqStr[0] = ('a'+file);
	sqStr[1] = ('1'+rank);

	std::cout << sqStr[0] << sqStr[1];
	return sqStr;
}

char *printMove(const int move)
{
	static char moveStr[6];
	int from_file = FROMSQ(move) % 8;
	int from_rank = FROMSQ(move) / 8;
	int to_file = TOSQ(move) % 8;
	int to_rank = TOSQ(move) / 8;

	moveStr[0] = ('a'+from_file);
	moveStr[1] = ('1'+from_rank);
	moveStr[2] = ('a'+to_file);
	moveStr[3] = ('1'+to_rank);

	std::cout << moveStr[0] << moveStr[1] << moveStr[2] << moveStr[3];

	int promoted = PROM_PIECE(move);

	if (promoted)
	{
		// assume it's a queen right away
		char prom_char = 'q';
		if (promoted == wN || promoted == bN)
		{
			prom_char = 'n';
		}
		else if (promoted == wR || promoted == bR)
		{
			prom_char = 'r';
		}
		else if (promoted == wB || promoted == bB)
		{
			prom_char = 'b';
		}
		moveStr[4] = prom_char;
		std::cout << prom_char;
	}

	return moveStr;
}
