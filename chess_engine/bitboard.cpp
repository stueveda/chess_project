// bitboard functions
#ifndef BITBOARD_H
#define BITBOARD_H
#include "defs.h"

// count the number of 1's in a bitboard
int countSetBits(U64 bb)
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

// pass a bitboard in by reference, and pop the first occurence of a set bit
int popFirstSetBit(U64 &bb)
{
	if (bb == 0)
		return -1;

	for (int i = 0; i < 64; i++)
	{
		if (bb & 1 == 1)
		{
			bb = bb ^ 1;
			return i;
		}
	}
}


#endif