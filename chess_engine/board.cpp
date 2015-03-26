// file:			board.cpp
// author:			Dan Stueve

// this file contains the implementation of the Board class


#include "board.h"
#include <iostream>


// used for printBoard - corresponds to bitboardArray
char pieceLookup[] = ".PNBRQKpnbrqk";

// returns the bitboard of the specified piece type
U64 Board::getPieceBitboard(int piece_type)
{
	return bitboardArray[piece_type];
}

// sets the bitboard of the specified piece type
void Board::setPieceBitboard(int piece_type, U64 bb)
{
	bitboardArray[piece_type] = bb;
}

// returns the bitboard indicating the position of all white pieces
U64 Board::getWPieces()
{
	return	bitboardArray[wP] |
			bitboardArray[wN] |
			bitboardArray[wB] |
			bitboardArray[wR] |
			bitboardArray[wQ] |
			bitboardArray[wK];
}

// returns the bitboard indicating the position of all black pieces
U64 Board::getBPieces()
{
	return	bitboardArray[bP] |
			bitboardArray[bN] |
			bitboardArray[bB] |
			bitboardArray[bR] |
			bitboardArray[bQ] |
			bitboardArray[bK];
}

// returns the bitboard indicating the position of all pieces
U64 Board::getAllPieces()
{
	return getWPieces() | getBPieces();
}

// returns the bitboard indicating empty squares
U64 Board::getEmpty()
{
	return ~getAllPieces();
}

int Board::getPieceType(int sq)
{
	U64 bb = (1ULL << sq);
	for (int i = 0; i < 13; i++)
	{
		if ((bb & getPieceBitboard(i)) == bb)
		{
			return i;
		}
	}
}

// returns whether the specified square is attacked by the specified side
bool Board::isSqAttacked(const int sq, const bool side)
{
	int rank = sq / 8;
	int file = sq % 8;
	U64 t_bb; // temp bitboard for sliding pieces

	// if the attacking side is white
	if (side == WHITE)
	{
		/**************** PAWN ATTACKS *******************/
		// white pawns can't attack anything on the 1st or 2nd ranks
		if (rank > 1)
		{
			if (file != 0)
			{
				t_bb = 1ULL << sq - 9;
				if ((t_bb & bitboardArray[wP]) == t_bb)
				{
					return true;
				}
			}
			if (file != 7)
			{
				t_bb = 1ULL << sq - 7;
				if ((t_bb & bitboardArray[wP]) == t_bb)
				{
					return true;
				}
			}
		}

		/**************** KNIGHT ATTACKS *******************/
		if (rank < 7)
		{
			if (file < 6)
			{
				t_bb = 1ULL << sq + 10;
				if ((t_bb & bitboardArray[wN]) == t_bb)
				{
					return true;
				}
			}
			if (file > 1)
			{
				t_bb = 1ULL << sq + 6;
				if ((t_bb & bitboardArray[wN]) == t_bb)
				{
					return true;
				}
			}
		}
		if (rank < 6)
		{
			if (file < 7)
			{
				t_bb = 1ULL << sq + 17;
				if ((t_bb & bitboardArray[wN]) == t_bb)
				{
					return true;
				}
			}
			if (file > 0)
			{
				t_bb = 1ULL << sq + 15;
				if ((t_bb & bitboardArray[wN]) == t_bb)
				{
					return true;
				}
			}
		}
		if (rank > 0)
		{
			if (file < 6)
			{
				t_bb = 1ULL << sq - 6;
				if ((t_bb & bitboardArray[wN]) == t_bb)
				{
					return true;
				}
			}
			if (file > 1)
			{
				t_bb = 1ULL << sq - 10;
				if ((t_bb& bitboardArray[wN]) == t_bb)
				{
					return true;
				}
			}
		}
		if (rank > 1)
		{
			if (file < 7)
			{
				t_bb = 1ULL << sq - 15;
				if ((t_bb & bitboardArray[wN]) == t_bb)
				{
					return true;
				}
			}
			if (file > 0)
			{
				t_bb = 1ULL << sq - 17;
				if ((t_bb & bitboardArray[wN]) == t_bb)
				{
					return true;
				}
			}
		}

		/**************** BISHOP AND QUEEN ATTACKS *******************/
		// upper right diagonal
		for (int t_sq = sq + 9; t_sq < 64 && t_sq >= 0; t_sq += 9)
		{
			// if we've moved over the right edge (H file), break
			if (t_sq % 8 == 0)
			{
				break;
			}
			t_bb = 1ULL << t_sq;
			// if there's a piece on the square
			if ((t_bb & getAllPieces()) == t_bb)
			{
				if ((t_bb & bitboardArray[wB]) == t_bb ||
					(t_bb & bitboardArray[wQ]) == t_bb)
				{
					return true;
				}
				// if it's a different piece, break
				else
				{
					break;
				}
			}
		}
		// lower right diagonal
		for (int t_sq = sq - 7; t_sq < 64 && t_sq >= 0; t_sq -= 7)
		{
			// if we've moved over the right edge (H file), break
			if (t_sq % 8 == 0)
			{
				break;
			}
			t_bb = 1ULL << t_sq;
			// if there's a piece on the square
			if ((t_bb & getAllPieces()) == t_bb)
			{
				if ((t_bb & bitboardArray[wB]) == t_bb ||
					(t_bb & bitboardArray[wQ]) == t_bb)
				{
					return true;
				}
				// if it's a different piece, break
				else
				{
					break;
				}
			}
		}
		// lower left diagonal
		for (int t_sq = sq - 9; t_sq < 64 && t_sq >= 0; t_sq -= 9)
		{
			// if we've moved over the left edge (A file), break
			if (t_sq % 8 == 7)
			{
				break;
			}
			t_bb = 1ULL << t_sq;
			// if there's a piece on the square
			if ((t_bb & getAllPieces()) == t_bb)
			{
				if ((t_bb & bitboardArray[wB]) == t_bb ||
					(t_bb & bitboardArray[wQ]) == t_bb)
				{
					return true;
				}
				// if it's a different piece, break
				else
				{
					break;
				}
			}
		}
		// upper left diagonal
		for (int t_sq = sq + 7; t_sq < 64 && t_sq >= 0; t_sq += 7)
		{
			// if we've moved over the left edge (A file), break
			if (t_sq % 8 == 7)
			{
				break;
			}
			t_bb = 1ULL << t_sq;
			// if there's a piece on the square
			if ((t_bb & getAllPieces()) == t_bb)
			{
				if ((t_bb & bitboardArray[wB]) == t_bb ||
					(t_bb & bitboardArray[wQ]) == t_bb)
				{
					return true;
				}
				// if it's a different piece, break
				else
				{
					break;
				}
			}
		}

		/**************** ROOK AND QUEEN ATTACKS *******************/
		// up direction
		for (int t_sq = sq + 8; t_sq < 64 && t_sq >= 0; t_sq += 8)
		{
			t_bb = 1ULL << t_sq;
			// if there's a piece on the square
			if ((t_bb & getAllPieces()) == t_bb)
			{
				if ((t_bb & bitboardArray[wR]) == t_bb ||
					(t_bb & bitboardArray[wQ]) == t_bb)
				{
					return true;
				}
				// if it's a different piece, break
				else
				{
					break;
				}
			}
		}
		// right direction
		for (int t_sq = sq + 1; t_sq < 64 && t_sq >= 0; t_sq += 1)
		{
			// if we've moved over the right edge (H file), break
			if (t_sq % 8 == 0)
			{
				break;
			}
			t_bb = 1ULL << t_sq;
			// if there's a piece on the square
			if ((t_bb & getAllPieces()) == t_bb)
			{
				if ((t_bb & bitboardArray[wR]) == t_bb ||
					(t_bb & bitboardArray[wQ]) == t_bb)
				{
					return true;
				}
				// if it's a different piece, break
				else
				{
					break;
				}
			}
		}
		// down direction
		for (int t_sq = sq - 8; t_sq < 64 && t_sq >= 0; t_sq -= 8)
		{
			t_bb = 1ULL << t_sq;
			// if there's a piece on the square
			if ((t_bb & getAllPieces()) == t_bb)
			{
				if ((t_bb & bitboardArray[wR]) == t_bb ||
					(t_bb & bitboardArray[wQ]) == t_bb)
				{
					return true;
				}
				// if it's a different piece, break
				else
				{
					break;
				}
			}
		}
		// left direction
		for (int t_sq = sq - 1; t_sq < 64 && t_sq >= 0; t_sq -= 1)
		{
			// if we've moved over the right edge (H file), break
			if (t_sq % 8 == 7)
			{
				break;
			}
			t_bb = 1ULL << t_sq;
			// if there's a piece on the square
			if ((t_bb & getAllPieces()) == t_bb)
			{
				if ((t_bb & bitboardArray[wR]) == t_bb ||
					(t_bb & bitboardArray[wQ]) == t_bb)
				{
					return true;
				}
				// if it's a different piece, break
				else
				{
					break;
				}
			}
		}
		/**************** KING ATTACKS *******************/
		if (rank < 7)
		{
			// test above
			t_bb = 1ULL << sq + 8;
			if ((t_bb & bitboardArray[wK]) == t_bb)
			{
				return true;
			}
			// test above and to right
			if (file < 7)
			{
				t_bb = 1ULL << sq + 9;
				if ((t_bb & bitboardArray[wK]) == t_bb)
				{
					return true;
				}
			}
			// test above and to left
			if (file > 0)
			{
				t_bb = 1ULL << sq + 7;
				if ((t_bb & bitboardArray[wK]) == t_bb)
				{
					return true;
				}
			}
		}

		if (rank > 0)
		{
			// test below
			t_bb = 1ULL << sq - 8;
			if ((t_bb & bitboardArray[wK]) == t_bb)
			{
				return true;
			}
			// test below and to right
			if (file < 7)
			{
				t_bb = 1ULL << sq - 7;
				if ((t_bb & bitboardArray[wK]) == t_bb)
				{
					return true;
				}
			}
			// test below and to left
			if (file > 0)
			{
				t_bb = 1ULL << sq - 9;
				if ((t_bb & bitboardArray[wK]) == t_bb)
				{
					return true;
				}
			}
		}
		// test left
		if (file > 0)
		{
			t_bb = 1ULL << sq - 1;
			if ((t_bb & bitboardArray[wK]) == t_bb)
			{
				return true;
			}
		}
		// test right
		if (file < 7)
		{
			t_bb = 1ULL << sq + 1;
			if ((t_bb & bitboardArray[wK]) == t_bb)
			{
				return true;
			}
		}
		return false;
	}

	// if the attacking side is black
	else
	{
		/**************** PAWN ATTACKS *******************/
		// black pawns can't attack anything on the 7th or 8th ranks
		if (rank < 6)
		{
			// check up and left
			if (file != 0)
			{
				t_bb = 1ULL << sq + 7;
				if ((t_bb & bitboardArray[bP]) == t_bb)
				{
					return true;
				}
			}
			// check up and right
			if (file != 7)
			{
				t_bb = 1ULL << sq + 9;
				if ((t_bb & bitboardArray[bP]) == t_bb)
				{
					return true;
				}
			}
		}

		/**************** KNIGHT ATTACKS *******************/
		if (rank < 7)
		{
			if (file < 6)
			{
				t_bb = 1ULL << sq + 10;
				if ((t_bb & bitboardArray[bN]) == t_bb)
				{
					return true;
				}
			}
			if (file > 1)
			{
				t_bb = 1ULL << sq + 6;
				if ((t_bb & bitboardArray[bN]) == t_bb)
				{
					return true;
				}
			}
		}
		if (rank < 6)
		{
			if (file < 7)
			{
				t_bb = 1ULL << sq + 17;
				if ((t_bb & bitboardArray[bN]) == t_bb)
				{
					return true;
				}
			}
			if (file > 0)
			{
				t_bb = 1ULL << sq + 15;
				if ((t_bb & bitboardArray[bN]) == t_bb)
				{
					return true;
				}
			}
		}
		if (rank > 0)
		{
			if (file < 6)
			{
				t_bb = 1ULL << sq - 6;
				if ((t_bb & bitboardArray[bN]) == t_bb)
				{
					return true;
				}
			}
			if (file > 1)
			{
				t_bb = 1ULL << sq - 10;
				if ((t_bb& bitboardArray[bN]) == t_bb)
				{
					return true;
				}
			}
		}
		if (rank > 1)
		{
			if (file < 7)
			{
				t_bb = 1ULL << sq - 15;
				if ((t_bb & bitboardArray[bN]) == t_bb)
				{
					return true;
				}
			}
			if (file > 0)
			{
				t_bb = 1ULL << sq - 17;
				if ((t_bb & bitboardArray[bN]) == t_bb)
				{
					return true;
				}
			}
		}

		/**************** BISHOP AND QUEEN ATTACKS *******************/
		// upper right diagonal
		for (int t_sq = sq + 9; t_sq < 64 && t_sq >= 0; t_sq += 9)
		{
			// if we've moved over the right edge (H file), break
			if (t_sq % 8 == 0)
			{
				break;
			}
			t_bb = 1ULL << t_sq;
			// if there's a piece on the square
			if ((t_bb & getAllPieces()) == t_bb)
			{
				if ((t_bb & bitboardArray[bB]) == t_bb ||
					(t_bb & bitboardArray[bQ]) == t_bb)
				{
					return true;
				}
				// if it's a different piece, break
				else
				{
					break;
				}
			}
		}
		// lower right diagonal
		for (int t_sq = sq - 7; t_sq < 64 && t_sq >= 0; t_sq -= 7)
		{
			// if we've moved over the right edge (H file), break
			if (t_sq % 8 == 0)
			{
				break;
			}
			t_bb = 1ULL << t_sq;
			// if there's a piece on the square
			if ((t_bb & getAllPieces()) == t_bb)
			{
				if ((t_bb & bitboardArray[bB]) == t_bb ||
					(t_bb & bitboardArray[bQ]) == t_bb)
				{
					return true;
				}
				// if it's a different piece, break
				else
				{
					break;
				}
			}
		}
		// lower left diagonal
		for (int t_sq = sq - 9; t_sq < 64 && t_sq >= 0; t_sq -= 9)
		{
			// if we've moved over the left edge (A file), break
			if (t_sq % 8 == 7)
			{
				break;
			}
			t_bb = 1ULL << t_sq;
			// if there's a piece on the square
			if ((t_bb & getAllPieces()) == t_bb)
			{
				if ((t_bb & bitboardArray[bB]) == t_bb ||
					(t_bb & bitboardArray[bQ]) == t_bb)
				{
					return true;
				}
				// if it's a different piece, break
				else
				{
					break;
				}
			}
		}
		// upper left diagonal
		for (int t_sq = sq + 7; t_sq < 64 && t_sq >= 0; t_sq += 7)
		{
			// if we've moved over the left edge (A file), break
			if (t_sq % 8 == 7)
			{
				break;
			}
			t_bb = 1ULL << t_sq;
			// if there's a piece on the square
			if ((t_bb & getAllPieces()) == t_bb)
			{
				if ((t_bb & bitboardArray[bB]) == t_bb ||
					(t_bb & bitboardArray[bQ]) == t_bb)
				{
					return true;
				}
				// if it's a different piece, break
				else
				{
					break;
				}
			}
		}

		/**************** ROOK AND QUEEN ATTACKS *******************/
		// up direction
		for (int t_sq = sq + 8; t_sq < 64 && t_sq >= 0; t_sq += 8)
		{
			t_bb = 1ULL << t_sq;
			// if there's a piece on the square
			if ((t_bb & getAllPieces()) == t_bb)
			{
				if ((t_bb & bitboardArray[bR]) == t_bb ||
					(t_bb & bitboardArray[bQ]) == t_bb)
				{
					return true;
				}
				// if it's a different piece, break
				else
				{
					break;
				}
			}
		}
		// right direction
		for (int t_sq = sq + 1; t_sq < 64 && t_sq >= 0; t_sq += 1)
		{
			// if we've moved over the right edge (H file), break
			if (t_sq % 8 == 0)
			{
				break;
			}
			t_bb = 1ULL << t_sq;
			// if there's a piece on the square
			if ((t_bb & getAllPieces()) == t_bb)
			{
				if ((t_bb & bitboardArray[bR]) == t_bb ||
					(t_bb & bitboardArray[bQ]) == t_bb)
				{
					return true;
				}
				// if it's a different piece, break
				else
				{
					break;
				}
			}
		}
		// down direction
		for (int t_sq = sq - 8; t_sq < 64 && t_sq >= 0; t_sq -= 8)
		{
			t_bb = 1ULL << t_sq;
			// if there's a piece on the square
			if ((t_bb & getAllPieces()) == t_bb)
			{
				if ((t_bb & bitboardArray[bR]) == t_bb ||
					(t_bb & bitboardArray[bQ]) == t_bb)
				{
					return true;
				}
				// if it's a different piece, break
				else
				{
					break;
				}
			}
		}
		// left direction
		for (int t_sq = sq - 1; t_sq < 64 && t_sq >= 0; t_sq -= 1)
		{
			// if we've moved over the right edge (H file), break
			if (t_sq % 8 == 7)
			{
				break;
			}
			t_bb = 1ULL << t_sq;
			// if there's a piece on the square
			if ((t_bb & getAllPieces()) == t_bb)
			{
				if ((t_bb & bitboardArray[bR]) == t_bb ||
					(t_bb & bitboardArray[bQ]) == t_bb)
				{
					return true;
				}
				// if it's a different piece, break
				else
				{
					break;
				}
			}
		}
		/**************** KING ATTACKS *******************/
		if (rank < 7)
		{
			// test above
			t_bb = 1ULL << sq + 8;
			if ((t_bb & bitboardArray[bK]) == t_bb)
			{
				return true;
			}
			// test above and to right
			if (file < 7)
			{
				t_bb = 1ULL << sq + 9;
				if ((t_bb & bitboardArray[bK]) == t_bb)
				{
					return true;
				}
			}
			// test above and to left
			if (file > 0)
			{
				t_bb = 1ULL << sq + 7;
				if ((t_bb & bitboardArray[bK]) == t_bb)
				{
					return true;
				}
			}
		}

		if (rank > 0)
		{
			// test below
			t_bb = 1ULL << sq - 8;
			if ((t_bb & bitboardArray[bK]) == t_bb)
			{
				return true;
			}
			// test below and to right
			if (file < 7)
			{
				t_bb = 1ULL << sq - 7;
				if ((t_bb & bitboardArray[bK]) == t_bb)
				{
					return true;
				}
			}
			// test below and to left
			if (file > 0)
			{
				t_bb = 1ULL << sq - 9;
				if ((t_bb & bitboardArray[bK]) == t_bb)
				{
					return true;
				}
			}
		}
		// test left
		if (file > 0)
		{
			t_bb = 1ULL << sq - 1;
			if ((t_bb & bitboardArray[bK]) == t_bb)
			{
				return true;
			}
		}
		// test right
		if (file < 7)
		{
			t_bb = 1ULL << sq + 1;
			if ((t_bb & bitboardArray[bK]) == t_bb)
			{
				return true;
			}
		}
		return false;
	}
}

// sets up the initial state of the board
void Board::setInitial()
{
	setPieceBitboard(NONE, 0x0);
	// 2^8 + 2^9 + 2^10 + 2^11 + 2^12 + 2^13 + 2^14 + 2^15
	setPieceBitboard(wP, 0x000000000000FF00);
	// 2^1 + 2^6
	setPieceBitboard(wN, 0x0000000000000042);
	// 2^2 + 2^5
	setPieceBitboard(wB, 0x0000000000000024);
	// 2^0 + 2^7
	setPieceBitboard(wR, 0x0000000000000081);
	// 2^3
	setPieceBitboard(wQ, 1ULL << D1);
	// 2^4
	setPieceBitboard(wK, 1ULL << E1);

	// 2^48 + 2^49 + 2^50 + 2^51 + 2^52 + 2^53 + 2^54 + 2^55
	setPieceBitboard(bP, 0x00FF000000000000);
	// 2^57 + 2^62
	setPieceBitboard(bN, 0x4200000000000000);
	// 2^58 + 2^61
	setPieceBitboard(bB, 0x2400000000000000);
	// 2^56 + 2^63
	setPieceBitboard(bR, 0x8100000000000000);
	// 2^59
	setPieceBitboard(bQ, 1ULL << D8);
	// 2^60
	setPieceBitboard(bK, 1ULL << E8);

	w_king_castle = true;
	w_queen_castle = true;
	b_king_castle = true;
	b_queen_castle = true;
	ep_square = -1;
	ply = 1;
}

// removes all pieces from the board,
// sets en passant square to none,
// sets all castling permissions to true,
// sets the ply to 1
void Board::clearBoard()
{
	setPieceBitboard(NONE, 0ULL);
	setPieceBitboard(wP, 0ULL);
	setPieceBitboard(wN, 0ULL);
	setPieceBitboard(wB, 0ULL);
	setPieceBitboard(wR, 0ULL);
	setPieceBitboard(wQ, 0ULL);
	setPieceBitboard(wK, 0ULL);

	setPieceBitboard(bP, 0ULL);
	setPieceBitboard(bN, 0ULL);
	setPieceBitboard(bB, 0ULL);
	setPieceBitboard(bR, 0ULL);
	setPieceBitboard(bQ, 0ULL);
	setPieceBitboard(bK, 0ULL);

	w_king_castle = true;
	w_queen_castle = true;
	b_king_castle = true;
	b_queen_castle = true;
	ep_square = -1;
	ply = 1;
}

// prints the current board state to the screen
void Board::printBoard()
{
	int square;
	int i;
	std::cout << "    A B C D E F G H \n\n";
	for (int rank = 7; rank >= 0; rank--)
	{
		std::cout << rank + 1 << "   ";
		for (int file = 0; file < 8; file++)
		{
			square = file + rank * 8;
			U64 board_square = 1ULL << square;

			// if there's no piece on the square, print .
			if ((board_square & (~getAllPieces())) == board_square)
				std::cout << ". ";
			// otherwise, print the piece using the lookup array
			else
			{
				for (i = 0; i < 13; i++)
				{
					if ((board_square & getPieceBitboard(i)) == board_square)
						break;
				}
				std::cout << pieceLookup[i] << " ";
			}
		}
		std::cout << '\n';
	}
	std::cout << "\n";
	if (side_to_move == WHITE)
		std::cout << "White";
	else
		std::cout << "Black";
	std::cout << "'s turn\n";
	std::cout << "White castle: ";
	if (w_king_castle)
		std::cout << "O-O ";
	if (w_queen_castle)
		std::cout << "O-O-O";
	std::cout << "\n";
	std::cout << "Black castle: ";
	if (b_king_castle)
		std::cout << "O-O ";
	if (b_queen_castle)
		std::cout << "O-O-O";
	std::cout << "\n";
	if (ep_square != -1)
		std::cout << "en passant square: " << ep_square;

}

// sets the board state to a specified FEN format string
int Board::parseFEN(char *fen)
{
	clearBoard();

	int rank = 7;
	int file = 0;
	int piece_type;
	int count;
	int square;

	while ((rank >= 0) && (*fen))
	{
		// read in pieces and empty spaces
		count = 1;
		switch (*fen)
		{
			case 'p': piece_type = bP; break;
			case 'n': piece_type = bN; break;
			case 'b': piece_type = bB; break;
			case 'r': piece_type = bR; break;
			case 'q': piece_type = bQ; break;
			case 'k': piece_type = bK; break;

			case 'P': piece_type = wP; break;
			case 'N': piece_type = wN; break;
			case 'B': piece_type = wB; break;
			case 'R': piece_type = wR; break;
			case 'Q': piece_type = wQ; break;
			case 'K': piece_type = wK; break;

			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
				piece_type = 0;
				count = *fen - '0';
				break;

			case '/':
			case ' ':
				rank--;
				file = 0;
				fen++;
				continue;

			default:
				return -1;
		}

		for (int i = 0; i < count; i++)
		{
			square = rank * 8 + file;
			bitboardArray[piece_type] |= (1ULL << square);
			file++;
		}
		fen++;
	}
	
	// read in the side to move
	if (*fen == 'w')
		side_to_move = WHITE;
	else
		side_to_move = BLACK;

	// advance to castle permissions
	fen += 2;
	for (int i = 0; i < 4; i++)
	{
		if (*fen == ' ')
		{
			break;
		}

		switch (*fen)
		{
			case 'K':	w_king_castle = true;	break;
			case 'Q':	w_queen_castle = true;	break;
			case 'k':	b_king_castle = true;	break;
			case 'q':	b_queen_castle = true;	break;
			default:	break;
		}
		fen++;
	}
	fen++;

	// read in en passant square
	if (*fen != '-')
	{
		file = fen[0] - 'a';
		rank = fen[1] - '1';

		ep_square = file + rank * 8;
	}
	return 0;
}

void Board::printAttacked(const bool side)
{
	int square;
	int i;
	std::cout << "    A B C D E F G H \n\n";
	for (int rank = 7; rank >= 0; rank--)
	{
		std::cout << rank + 1 << "   ";
		for (int file = 0; file < 8; file++)
		{
			square = file + rank * 8;
			U64 board_square = 1ULL << square;
			// if the square is attacked, print 1
			if (isSqAttacked(square, side))
			{
				std::cout << "1 ";
			}
			// otherwise, print 0
			else
			{
				std::cout << "0 ";
			}
		}
		std::cout << '\n';
	}
	std::cout << "\n";
}


/************** MOVE GENERATION ***************/
void Board::addQuietMove(int move)
{
	move_list->moves[move_list->count].move = move;
	move_list->moves[move_list->count].value = 0;
	move_list->count++;
}

void Board::addCaptureMove(int move)
{
	move_list->moves[move_list->count].move = move;
	move_list->moves[move_list->count].value = 0;
	move_list->count++;
}

void Board::addEnPassantMove(int move)
{
	move_list->moves[move_list->count].move = move;
	move_list->moves[move_list->count].value = 0;
	move_list->count++;
}

void Board::generateAllMoves()
{
	move_list->count = 0;

	int sq;
	int rank;
	int file;
	U64 t_bb;
	

	if (side_to_move == WHITE)
	{
		// White pawn
		U64 piece_bb = getPieceBitboard(wP);
		int piece_count = countBits(piece_bb);
		U64 &ref_bb = piece_bb;
		for (int i = 0; i < piece_count; i++)
		{
			sq = popFirstSetBit(ref_bb);
			rank = sq / 8;
			file = sq % 8;
			
			t_bb = (1ULL << (sq + 8));
			if ((rank < 7) && ((getEmpty() & (t_bb)) == t_bb))
			{
				addWPawnMove(sq, (sq + 8));
				t_bb = (1ULL << (sq + 16));
				if ((rank == 1) && ((getEmpty() & (t_bb)) == t_bb))
				{
					addQuietMove(M_MOVE(sq,(sq + 16),NONE,NONE,PS_FLAG));
				}
			}

			t_bb = (1ULL << (sq + 7));
			if ((file != 0) && ((getBPieces() & t_bb) == t_bb))
			{
				addWPawnCapMove(sq, (sq+7), getPieceType(sq+7));
			}
			
			t_bb = (1ULL << (sq + 9));
			if ((file != 7) && ((getBPieces() & t_bb) == t_bb))
			{
				addWPawnCapMove(sq, (sq+9), getPieceType(sq+9));
			}

			if ((file != 0) && (sq + 7 == ep_square))
			{
				addCaptureMove(M_MOVE(sq, (sq+7), NONE, NONE, EP_FLAG));
			}
			if ((file != 7) && (sq + 9 == ep_square))
			{
				addCaptureMove(M_MOVE(sq, (sq+9), NONE, NONE, EP_FLAG));
			}
		}
	}
	else
	{
		// Black pawn
		U64 piece_bb = getPieceBitboard(bP);
		int piece_count = countBits(piece_bb);
		U64 &ref_bb = piece_bb;

		for (int i = 0; i < piece_count; i++)
		{
			sq = popFirstSetBit(ref_bb);
			rank = sq / 8;
			file = sq % 8;
			
			t_bb = (1ULL << (sq - 8));
			if ((rank > 0) && ((getEmpty() & (t_bb)) == t_bb))
			{
				addBPawnMove(sq, (sq - 8));
				t_bb = (1ULL << (sq - 16));
				if ((rank == 6) && ((getEmpty() & (t_bb)) == t_bb))
				{
					addQuietMove(M_MOVE(sq,(sq - 16),NONE,NONE,PS_FLAG));
				}
			}

			t_bb = (1ULL << (sq - 9));
			if ((file != 0) && ((getWPieces() & t_bb) == t_bb))
			{
				addBPawnCapMove(sq, (sq-9), getPieceType(sq-9));
			}
			
			t_bb = (1ULL << (sq - 7));
			if ((file != 7) && ((getWPieces() & t_bb) == t_bb))
			{
				addBPawnCapMove(sq, (sq-7), getPieceType(sq-7));
			}

			if ((file != 0) && (sq - 9 == ep_square))
			{
				addCaptureMove(M_MOVE(sq, (sq-9), NONE, NONE, EP_FLAG));
			}
			if ((file != 7) && (sq - 7 == ep_square))
			{
				addCaptureMove(M_MOVE(sq, (sq-7), NONE, NONE, EP_FLAG));
			}
		}
	}
}

void Board::printMoveList()
{
	int index = 0;
	int value = 0;
	int move = 0;
	std::cout << "Move list: " << move_list->count << " moves.\n";

	for (index = 0; index < move_list->count; index++)
	{
		move = move_list->moves[index].move;
		value = move_list->moves[index].value;

		std::cout << "move: ";
		printMove(move);
		std::cout << "   value: " << value << "\n";
	}
}

void Board::addWPawnCapMove(const int from, const int to, const int cap)
{
	if (from / 8 == 6)
	{
		addCaptureMove(M_MOVE(from, to, cap, wQ, 0));
		addCaptureMove(M_MOVE(from, to, cap, wR, 0));
		addCaptureMove(M_MOVE(from, to, cap, wB, 0));
		addCaptureMove(M_MOVE(from, to, cap, wN, 0));
	}
	else
	{
		addCaptureMove(M_MOVE(from, to, NONE, NONE, 0));
	}
}

void Board::addWPawnMove(const int from, const int to)
{
	if (from / 8 == 6)
	{
		addQuietMove(M_MOVE(from, to, NONE, wQ, 0));
		addQuietMove(M_MOVE(from, to, NONE, wR, 0));
		addQuietMove(M_MOVE(from, to, NONE, wB, 0));
		addQuietMove(M_MOVE(from, to, NONE, wN, 0));
	}
	else
	{
		addQuietMove(M_MOVE(from, to, NONE, NONE, 0));
	}
}

void Board::addBPawnCapMove(const int from, const int to, const int cap)
{
	if (from / 8 == 1)
	{
		addCaptureMove(M_MOVE(from, to, cap, bQ, 0));
		addCaptureMove(M_MOVE(from, to, cap, bR, 0));
		addCaptureMove(M_MOVE(from, to, cap, bB, 0));
		addCaptureMove(M_MOVE(from, to, cap, bN, 0));
	}
	else
	{
		addCaptureMove(M_MOVE(from, to, NONE, NONE, 0));
	}
}

void Board::addBPawnMove(const int from, const int to)
{
	if (from / 8 == 1)
	{
		addQuietMove(M_MOVE(from, to, NONE, bQ, 0));
		addQuietMove(M_MOVE(from, to, NONE, bR, 0));
		addQuietMove(M_MOVE(from, to, NONE, bB, 0));
		addQuietMove(M_MOVE(from, to, NONE, bN, 0));
	}
	else
	{
		addQuietMove(M_MOVE(from, to, NONE, NONE, 0));
	}
}