// file:			board.cpp
// author:			Dan Stueve

// this file contains the implementation of the Board class


#include "board.h"
#include <iostream>


// used for printBoard - corresponds to bitboardArray
const char pieceLookup[] = ".PNBRQKpnbrqk";

// the attacking directions of rook and bishop sliding pieces
const int rookDirs[] = {8, 1, -8, -1};
const int bishopDirs[] = {9, -7, -9, 7};

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
	for (int i = 1; i < 13; i++)
	{
		if ((bb & getPieceBitboard(i)) == bb)
		{
			return i;
		}
	}
	return NONE;
}

// returns whether the specified square is attacked by the specified side
bool Board::isSqAttacked(const int sq, const bool side)
{
	int rank = sq / 8;
	int file = sq % 8;
	int dir;
	U64 t_bb; // temp bitboard for sliding pieces

	// if the attacking side is white
	if (side == WHITE)
	{
		/**************** PAWN ATTACKS *******************/
		if (sq + 9 >= 0 && file > 0 && (getPieceType(sq - 9) == wP))
		{
			return true;
		}
		if (sq + 7 >= 0 && file < 7 && (getPieceType(sq - 7) == wP))
		{
			return true;
		}

		/**************** KNIGHT ATTACKS *******************/
		// up 2 right 1 => +17
		if (rank < 6 && file < 7 && (getPieceType(sq + 17) == wN))
		{
			return true;
		}
		// up 1 right 2 => +10
		if (rank < 7 && file < 6 && (getPieceType(sq + 10) == wN))
		{
			return true;
		}
		// down 2 right 1 => -15
		if (rank > 1 && file < 7 && (getPieceType(sq - 15) == wN))
		{
			return true;
		}
		// down 1 right 2 => -6
		if (rank > 1 && file < 6 && (getPieceType(sq - 6) == wN))
		{
			return true;
		}
		// up 2 left 1 => +15
		if (rank < 6 && file > 0 && (getPieceType(sq + 15) == wN))
		{
			return true;
		}
		// up 1 left 2 => +6
		if (rank < 7 && file > 1 && (getPieceType(sq + 6) == wN))
		{
			return true;
		}
		// down 2 left 1 => -17
		if (rank > 1 && file > 0 && (getPieceType(sq - 17) == wN))
		{
			return true;
		}
		// down 1 left 2 => -10
		if (rank > 1 && file > 1 && (getPieceType(sq - 10) == wN))
		{
			return true;
		}

		/**************** BISHOP AND QUEEN ATTACKS *******************/
		for (int i = 0; i < 4; i++)
		{
			dir = bishopDirs[i];
			for (int t_sq = sq + dir; t_sq < 64 && t_sq >= 0; t_sq += dir)
			{
				if ((t_sq % 8 == 0) && (((dir % 8 + 8) % 8) == 1))
				{
					break;
				}
				if ((t_sq % 8 == 7) && (((dir % 8 + 8) % 8) == 7))
				{
					break;
				}
				int piece = getPieceType(t_sq);
				if ((piece == wB) || (piece == wQ))
				{
					return true;
				}
				else if (piece == NONE)
				{
					continue;
				}
				else
				{
					break;
				}
			}
		}

		/**************** ROOK AND QUEEN ATTACKS *******************/
		for (int i = 0; i < 4; i++)
		{
			dir = rookDirs[i];
			for (int t_sq = sq + dir; t_sq < 64 && t_sq >= 0; t_sq += dir)
			{
				if ((t_sq % 8 == 0) && (((dir % 8 + 8) % 8) == 1))
				{
					break;
				}
				if ((t_sq % 8 == 7) && (((dir % 8 + 8) % 8) == 7))
				{
					break;
				}
				int piece = getPieceType(t_sq);
				if ((piece == wR) || (piece == wQ))
				{
					return true;
				}
				else if (piece == NONE)
				{
					continue;
				}
				else
				{
					break;
				}
			}
		}

		/**************** KING ATTACKS *******************/
		if (rank < 7 && (getPieceType(sq + 8) == wK))
		{
			return true;
		}
		if (rank < 7 && file < 7 && (getPieceType(sq + 9) == wK))
		{
			return true;
		}
		if (rank < 7 && file > 0 && (getPieceType(sq + 7) == wK))
		{
			return true;
		}
		if (rank > 0 && (getPieceType(sq - 8) == wK))
		{
			return true;
		}
		if (rank > 0 && file < 7 && (getPieceType(sq - 7) == wK))
		{
			return true;
		}
		if (rank > 0 && file > 0 && (getPieceType(sq - 9) == wK))
		{
			return true;
		}
		if (file > 0 && (getPieceType(sq + 1) == wK))
		{
			return true;
		}
		if (file < 7 && (getPieceType(sq - 1) == wK))
		{
			return true;
		}
		return false;
	}

	// if the attacking side is black
	else
	{
		/**************** PAWN ATTACKS *******************/
		if (sq + 7 < 64 && file > 0 && (getPieceType(sq + 7) == bP))
		{
			return true;
		}
		if (sq + 9 < 64 && file < 7 && (getPieceType(sq + 9) == bP))
		{
			return true;
		}

		/**************** KNIGHT ATTACKS *******************/
		// up 2 right 1 => +17
		if (rank < 6 && file < 7 && (getPieceType(sq + 17) == bN))
		{
			return true;
		}
		// up 1 right 2 => +10
		if (rank < 7 && file < 6 && (getPieceType(sq + 10) == bN))
		{
			return true;
		}
		// down 2 right 1 => -15
		if (rank > 1 && file < 7 && (getPieceType(sq - 15) == bN))
		{
			return true;
		}
		// down 1 right 2 => -6
		if (rank > 1 && file < 6 && (getPieceType(sq - 6) == bN))
		{
			return true;
		}
		// up 2 left 1 => +15
		if (rank < 6 && file > 0 && (getPieceType(sq + 15) == bN))
		{
			return true;
		}
		// up 1 left 2 => +6
		if (rank < 7 && file > 1 && (getPieceType(sq + 6) == bN))
		{
			return true;
		}
		// down 2 left 1 => -17
		if (rank > 1 && file > 0 && (getPieceType(sq - 17) == bN))
		{
			return true;
		}
		// down 1 left 2 => -10
		if (rank > 1 && file > 1 && (getPieceType(sq - 10) == bN))
		{
			return true;
		}

		/**************** BISHOP AND QUEEN ATTACKS *******************/
		for (int i = 0; i < 4; i++)
		{
			dir = bishopDirs[i];
			for (int t_sq = sq + dir; t_sq < 64 && t_sq >= 0; t_sq += dir)
			{
				if ((t_sq % 8 == 0) && (((dir % 8 + 8) % 8) == 1))
				{
					break;
				}
				if ((t_sq % 8 == 7) && (((dir % 8 + 8) % 8) == 7))
				{
					break;
				}
				int piece = getPieceType(t_sq);
				if ((piece == bB) || (piece == bQ))
				{
					return true;
				}
				else if (piece == NONE)
				{
					continue;
				}
				else
				{
					break;
				}
			}
		}

		/**************** ROOK AND QUEEN ATTACKS *******************/
		for (int i = 0; i < 4; i++)
		{
			dir = rookDirs[i];
			for (int t_sq = sq + dir; t_sq < 64 && t_sq >= 0; t_sq += dir)
			{
				if ((t_sq % 8 == 0) && (((dir % 8 + 8) % 8) == 1))
				{
					break;
				}
				if ((t_sq % 8 == 7) && (((dir % 8 + 8) % 8) == 7))
				{
					break;
				}
				int piece = getPieceType(t_sq);
				if ((piece == bR) || (piece == bQ))
				{
					return true;
				}
				else if (piece == NONE)
				{
					continue;
				}
				else
				{
					break;
				}
			}
		}

		/**************** KING ATTACKS *******************/
		if (rank < 7 && (getPieceType(sq + 8) == bK))
		{
			return true;
		}
		if (rank < 7 && file < 7 && (getPieceType(sq + 9) == bK))
		{
			return true;
		}
		if (rank < 7 && file > 0 && (getPieceType(sq + 7) == bK))
		{
			return true;
		}
		if (rank > 0 && (getPieceType(sq - 8) == bK))
		{
			return true;
		}
		if (rank > 0 && file < 7 && (getPieceType(sq - 7) == bK))
		{
			return true;
		}
		if (rank > 0 && file > 0 && (getPieceType(sq - 9) == bK))
		{
			return true;
		}
		if (file > 0 && (getPieceType(sq + 1) == bK))
		{
			return true;
		}
		if (file < 7 && (getPieceType(sq - 1) == bK))
		{
			return true;
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
	game_ply = 1;
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
	game_ply = 1;
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
			if (getPieceType(square) == NONE)
				std::cout << ". ";
			// otherwise, print the piece using the lookup array
			else
			{
				i = getPieceType(square);
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
	else
	{
		ep_square = -1;
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

void Board::addCapOrQuiet(int piece_type, int from, int to, bool side)
{
	if (side == WHITE)
	{
		if (piece_type == NONE)
		{
			addQuietMove(M_MOVE(from, to, NONE, NONE, 0));
		}
		else if (piece_type >= bP && piece_type <= bK)
		{
			addCaptureMove(M_MOVE(from, to, piece_type, NONE, 0));
		}
	}
	else
	{
		if (piece_type == NONE)
		{
			addQuietMove(M_MOVE(from, to, NONE, NONE, 0));
		}
		else if (piece_type >= wP && piece_type <= wK)
		{
			addCaptureMove(M_MOVE(from, to, piece_type, NONE, 0));
		}
	}
}

void Board::generateAllMoves()
{
	move_list->count = 0;

	int sq;
	int rank;
	int file;
	int t_piece;
	U64 t_bb;
	

	if (side_to_move == WHITE)
	{
		U64 piece_bb;
		int piece_count;
		for (int piece_type = wP; piece_type <= wK; piece_type++)
		{
			piece_bb = getPieceBitboard(piece_type);
			int piece_count = countBits(piece_bb);
			if (piece_count == 0)
			{
				continue;
			}
			U64 &ref_bb = piece_bb;
			/************************** WHITE PAWNS ***********************/
			if (piece_type == wP)
			{
				for (int i = 0; i < piece_count; i++)
				{
					sq = popFirstSetBit(ref_bb);
					rank = sq / 8;
					file = sq % 8;

					if ((rank < 7) && (getPieceType(sq + 8) == NONE))
					{
						addWPawnMove(sq, (sq + 8));
						if ((rank == 1) && (getPieceType(sq + 16) == NONE))
						{
							addQuietMove(M_MOVE(sq,(sq + 16),NONE,NONE,PS_FLAG));
						}
					}

					t_piece = getPieceType(sq + 7);
					if (file != 0 && t_piece >= bP && t_piece <= bK)
					{
						addWPawnCapMove(sq, (sq+7), t_piece);
					}
					
					t_piece = getPieceType(sq + 9);
					if (file != 0 && t_piece >= bP && t_piece <= bK)
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
			/************ WHITE BISHOPS ***********/
			if (piece_type == wB)
			{
				for (int i = 0; i < piece_count; i++)
				{
					sq = popFirstSetBit(ref_bb);
					rank = sq / 8;
					file = sq % 8;
					
					for (int j = 0; j < 4; j++)
					{
						int dir = bishopDirs[j];
						for (int t_sq = sq + dir; t_sq < 64 && t_sq >= 0; t_sq += dir)
						{
							if ((t_sq % 8 == 0) && (((dir % 8 + 8) % 8) == 1))
							{
								break;
							}
							if ((t_sq % 8 == 7) && (((dir % 8 + 8) % 8) == 7))
							{
								break;
							}
							t_piece = getPieceType(t_sq);
							addCapOrQuiet(t_piece, sq, t_sq, WHITE);
							if (t_piece != NONE)
							{
								break;
							}
						}
					}
				}
			}
			/************ WHITE ROOKS ***********/
			if (piece_type == wR)
			{
				for (int i = 0; i < piece_count; i++)
				{
					sq = popFirstSetBit(ref_bb);
					rank = sq / 8;
					file = sq % 8;
					
					for (int j = 0; j < 4; j++)
					{
						int dir = rookDirs[j];
						for (int t_sq = sq + dir; t_sq < 64 && t_sq >= 0; t_sq += dir)
						{
							if ((t_sq % 8 == 0) && (((dir % 8 + 8) % 8) == 1))
							{
								break;
							}
							if ((t_sq % 8 == 7) && (((dir % 8 + 8) % 8) == 7))
							{
								break;
							}
							t_piece = getPieceType(t_sq);
							addCapOrQuiet(t_piece, sq, t_sq, WHITE);
							if (t_piece != NONE)
							{
								break;
							}
						}
					}
				}
			}
			/************* WHITE KNIGHTS ************************/
			if (piece_type == wN)
			{
				for (int i = 0; i < piece_count; i++)
				{
					sq = popFirstSetBit(ref_bb);
					rank = sq / 8;
					file = sq % 8;
					int t_sq;
					
					if (rank < 6 && file < 7)
					{
						t_sq = sq + 17;
						t_piece = getPieceType(t_sq);
						addCapOrQuiet(t_piece, sq, t_sq, WHITE);
					}
					if (rank < 7 && file < 6)
					{
						t_sq = sq + 10;
						t_piece = getPieceType(t_sq);
						addCapOrQuiet(t_piece, sq, t_sq, WHITE);
					}
					if (rank > 1 && file < 7)
					{
						t_sq = sq - 15;
						t_piece = getPieceType(t_sq);
						addCapOrQuiet(t_piece, sq, t_sq, WHITE);
					}
					if (rank > 1 && file < 6)
					{
						t_sq = sq - 6;
						t_piece = getPieceType(t_sq);
						addCapOrQuiet(t_piece, sq, t_sq, WHITE);
					}
					if (rank < 6 && file > 0)
					{
						t_sq = sq + 15;
						t_piece = getPieceType(t_sq);
						addCapOrQuiet(t_piece, sq, t_sq, WHITE);
					}
					if (rank < 7 && file > 1)
					{
						t_sq = sq + 6;
						t_piece = getPieceType(t_sq);
						addCapOrQuiet(t_piece, sq, t_sq, WHITE);
					}
					if (rank > 1 && file > 0)
					{
						t_sq = sq - 17;
						t_piece = getPieceType(t_sq);
						addCapOrQuiet(t_piece, sq, t_sq, WHITE);
					}
					if (rank > 1 && file > 1)
					{
						t_sq = sq - 10;
						t_piece = getPieceType(t_sq);
						addCapOrQuiet(t_piece, sq, t_sq, WHITE);
					}
				}
			}
			/********************** WHITE QUEENS **************************/
			if (piece_type == wQ)
			{
				for (int i = 0; i < piece_count; i++)
				{
					sq = popFirstSetBit(ref_bb);
					rank = sq / 8;
					file = sq % 8;
					
					for (int j = 0; j < 4; j++)
					{
						int dir = rookDirs[j];
						for (int t_sq = sq + dir; t_sq < 64 && t_sq >= 0; t_sq += dir)
						{
							if ((t_sq % 8 == 0) && (((dir % 8 + 8) % 8) == 1))
							{
								break;
							}
							if ((t_sq % 8 == 7) && (((dir % 8 + 8) % 8) == 7))
							{
								break;
							}
							t_piece = getPieceType(t_sq);
							addCapOrQuiet(t_piece, sq, t_sq, WHITE);
							if (t_piece != NONE)
							{
								break;
							}
						}
					}
					for (int j = 0; j < 4; j++)
					{
						int dir = bishopDirs[j];
						for (int t_sq = sq + dir; t_sq < 64 && t_sq >= 0; t_sq += dir)
						{
							if ((t_sq % 8 == 0) && (((dir % 8 + 8) % 8) == 1))
							{
								break;
							}
							if ((t_sq % 8 == 7) && (((dir % 8 + 8) % 8) == 7))
							{
								break;
							}
							t_piece = getPieceType(t_sq);
							addCapOrQuiet(t_piece, sq, t_sq, WHITE);
							if (t_piece != NONE)
							{
								break;
							}
						}
					}
				}
			}
			/**************************** WHITE KING *********************/
			if (piece_type == wK)
			{
				for (int i = 0; i < piece_count; i++)
				{
					sq = popFirstSetBit(ref_bb);
					rank = sq / 8;
					file = sq % 8;

					if (rank < 7)
					{
						t_piece = getPieceType(sq + 8);
						addCapOrQuiet(t_piece, sq, sq + 8, WHITE);
					}
					if (rank < 7 && file < 7)
					{
						t_piece = getPieceType(sq + 9);
						addCapOrQuiet(t_piece, sq, sq + 9, WHITE);
					}
					if (rank < 7 && file > 0)
					{
						t_piece = getPieceType(sq + 7);
						addCapOrQuiet(t_piece, sq, sq + 7, WHITE);
					}
					if (rank > 0)
					{
						t_piece = getPieceType(sq - 8);
						addCapOrQuiet(t_piece, sq, sq - 8, WHITE);
					}
					if (rank > 0 && file < 7)
					{
						t_piece = getPieceType(sq - 7);
						addCapOrQuiet(t_piece, sq, sq - 7, WHITE);
					}
					if (rank > 0 && file > 0)
					{
						t_piece = getPieceType(sq - 9);
						addCapOrQuiet(t_piece, sq, sq - 9, WHITE);
					}
					if (file > 0)
					{
						t_piece = getPieceType(sq + 1);
						addCapOrQuiet(t_piece, sq, sq + 1, WHITE);
					}
					if (file < 7)
					{
						t_piece = getPieceType(sq - 1);
						addCapOrQuiet(t_piece, sq, sq - 1, WHITE);
					}
				}
			}
		}
		/********************** WHITE CASTLING *********************/
			if (w_king_castle &&
				getPieceType(F1) == NONE &&
				getPieceType(G1) == NONE)
			{
				if (!isSqAttacked(E1, BLACK) &&
					!isSqAttacked(F1, BLACK) &&
					!isSqAttacked(G1, BLACK))
				{
					addQuietMove(M_MOVE(E1, G1, NONE, NONE, CAS_FLAG));
				}
			}
			if (w_queen_castle &&
				getPieceType(D1) == NONE &&
				getPieceType(C1) == NONE &&
				getPieceType(B1) == NONE)
			{
				if (!isSqAttacked(E1, BLACK) &&
					!isSqAttacked(D1, BLACK) &&
					!isSqAttacked(C1, BLACK))
				{
					addQuietMove(M_MOVE(E1, C1, NONE, NONE, CAS_FLAG));
				}
			}
	}
	else
	{
		U64 piece_bb;
		int piece_count;
		for (int piece_type = bP; piece_type <= bK; piece_type++)
		{
			piece_bb = getPieceBitboard(piece_type);
			int piece_count = countBits(piece_bb);
			if (piece_count == 0)
			{
				continue;
			}
			U64 &ref_bb = piece_bb;
			/************************** BLACK PAWNS ***********************/
			if (piece_type == bP)
			{
				for (int i = 0; i < piece_count; i++)
				{
					sq = popFirstSetBit(ref_bb);
					rank = sq / 8;
					file = sq % 8;

					if ((rank < 7) && (getPieceType(sq + 8) == NONE))
					{
						addWPawnMove(sq, (sq + 8));
						if ((rank == 1) && (getPieceType(sq + 16) == NONE))
						{
							addQuietMove(M_MOVE(sq,(sq + 16),NONE,NONE,PS_FLAG));
						}
					}

					t_piece = getPieceType(sq + 7);
					if (file != 0 && t_piece >= bP && t_piece <= bK)
					{
						addWPawnCapMove(sq, (sq+7), t_piece);
					}
					
					t_piece = getPieceType(sq + 9);
					if (file != 0 && t_piece >= bP && t_piece <= bK)
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
			/************************** BLACK BISHOPS **********************/
			if (piece_type == bB)
			{
				for (int i = 0; i < piece_count; i++)
				{
					sq = popFirstSetBit(ref_bb);
					rank = sq / 8;
					file = sq % 8;
					
					for (int j = 0; j < 4; j++)
					{
						int dir = bishopDirs[j];
						for (int t_sq = sq + dir; t_sq < 64 && t_sq >= 0; t_sq += dir)
						{
							if ((t_sq % 8 == 0) && (((dir % 8 + 8) % 8) == 1))
							{
								break;
							}
							if ((t_sq % 8 == 7) && (((dir % 8 + 8) % 8) == 7))
							{
								break;
							}
							t_piece = getPieceType(t_sq);
							addCapOrQuiet(t_piece, sq, t_sq, BLACK);
							if (t_piece != NONE)
							{
								break;
							}
						}
					}
				}
			}
			/************************* BLACK ROOKS *****************************/
			if (piece_type == bR)
			{
				for (int i = 0; i < piece_count; i++)
				{
					sq = popFirstSetBit(ref_bb);
					rank = sq / 8;
					file = sq % 8;
					
					for (int j = 0; j < 4; j++)
					{
						int dir = rookDirs[j];
						for (int t_sq = sq + dir; t_sq < 64 && t_sq >= 0; t_sq += dir)
						{
							if ((t_sq % 8 == 0) && (((dir % 8 + 8) % 8) == 1))
							{
								break;
							}
							if ((t_sq % 8 == 7) && (((dir % 8 + 8) % 8) == 7))
							{
								break;
							}
							t_piece = getPieceType(t_sq);
							addCapOrQuiet(t_piece, sq, t_sq, BLACK);
							if (t_piece != NONE)
							{
								break;
							}
						}
					}
				}
			}
			/**************************** BLACK KNIGHTS ************************/
			if (piece_type == bN)
			{
				for (int i = 0; i < piece_count; i++)
				{
					sq = popFirstSetBit(ref_bb);
					rank = sq / 8;
					file = sq % 8;
					int t_sq;
					
					if (rank < 6 && file < 7)
					{
						t_sq = sq + 17;
						t_piece = getPieceType(t_sq);
						addCapOrQuiet(t_piece, sq, t_sq, BLACK);
					}
					if (rank < 7 && file < 6)
					{
						t_sq = sq + 10;
						t_piece = getPieceType(t_sq);
						addCapOrQuiet(t_piece, sq, t_sq, BLACK);
					}
					if (rank > 1 && file < 7)
					{
						t_sq = sq - 15;
						t_piece = getPieceType(t_sq);
						addCapOrQuiet(t_piece, sq, t_sq, BLACK);
					}
					if (rank > 1 && file < 6)
					{
						t_sq = sq - 6;
						t_piece = getPieceType(t_sq);
						addCapOrQuiet(t_piece, sq, t_sq, BLACK);
					}
					if (rank < 6 && file > 0)
					{
						t_sq = sq + 15;
						t_piece = getPieceType(t_sq);
						addCapOrQuiet(t_piece, sq, t_sq, BLACK);
					}
					if (rank < 7 && file > 1)
					{
						t_sq = sq + 6;
						t_piece = getPieceType(t_sq);
						addCapOrQuiet(t_piece, sq, t_sq, BLACK);
					}
					if (rank > 1 && file > 0)
					{
						t_sq = sq - 17;
						t_piece = getPieceType(t_sq);
						addCapOrQuiet(t_piece, sq, t_sq, BLACK);
					}
					if (rank > 1 && file > 1)
					{
						t_sq = sq - 10;
						t_piece = getPieceType(t_sq);
						addCapOrQuiet(t_piece, sq, t_sq, BLACK);
					}
				}
			}
			/************************** BLACK QUEENS **************************/
			if (piece_type == bQ)
			{
				for (int i = 0; i < piece_count; i++)
				{
					sq = popFirstSetBit(ref_bb);
					rank = sq / 8;
					file = sq % 8;
					
					for (int j = 0; j < 4; j++)
					{
						int dir = rookDirs[j];
						for (int t_sq = sq + dir; t_sq < 64 && t_sq >= 0; t_sq += dir)
						{
							if ((t_sq % 8 == 0) && (((dir % 8 + 8) % 8) == 1))
							{
								break;
							}
							if ((t_sq % 8 == 7) && (((dir % 8 + 8) % 8) == 7))
							{
								break;
							}
							t_piece = getPieceType(t_sq);
							addCapOrQuiet(t_piece, sq, t_sq, BLACK);
							if (t_piece != NONE)
							{
								break;
							}
						}
					}
					for (int j = 0; j < 4; j++)
					{
						int dir = bishopDirs[j];
						for (int t_sq = sq + dir; t_sq < 64 && t_sq >= 0; t_sq += dir)
						{
							if ((t_sq % 8 == 0) && (((dir % 8 + 8) % 8) == 1))
							{
								break;
							}
							if ((t_sq % 8 == 7) && (((dir % 8 + 8) % 8) == 7))
							{
								break;
							}
							t_piece = getPieceType(t_sq);
							addCapOrQuiet(t_piece, sq, t_sq, BLACK);
							if (t_piece != NONE)
							{
								break;
							}
						}
					}
				}
			}
			/**************************** BLACK KING ********************************/
			if (piece_type == bK)
			{
				for (int i = 0; i < piece_count; i++)
				{
					sq = popFirstSetBit(ref_bb);
					rank = sq / 8;
					file = sq % 8;

					if (rank < 7)
					{
						t_piece = getPieceType(sq + 8);
						addCapOrQuiet(t_piece, sq, sq + 8, BLACK);
					}
					if (rank < 7 && file < 7)
					{
						t_piece = getPieceType(sq + 9);
						addCapOrQuiet(t_piece, sq, sq + 9, BLACK);
					}
					if (rank < 7 && file > 0)
					{
						t_piece = getPieceType(sq + 7);
						addCapOrQuiet(t_piece, sq, sq + 7, BLACK);
					}
					if (rank > 0)
					{
						t_piece = getPieceType(sq - 8);
						addCapOrQuiet(t_piece, sq, sq - 8, BLACK);
					}
					if (rank > 0 && file < 7)
					{
						t_piece = getPieceType(sq - 7);
						addCapOrQuiet(t_piece, sq, sq - 7, BLACK);
					}
					if (rank > 0 && file > 0)
					{
						t_piece = getPieceType(sq - 9);
						addCapOrQuiet(t_piece, sq, sq - 9, BLACK);
					}
					if (file > 0)
					{
						t_piece = getPieceType(sq + 1);
						addCapOrQuiet(t_piece, sq, sq + 1, BLACK);
					}
					if (file < 7)
					{
						t_piece = getPieceType(sq - 1);
						addCapOrQuiet(t_piece, sq, sq - 1, BLACK);
					}
				}
			}
		}
		/********************** BLACK CASTLING *********************/
		if (b_king_castle &&
			getPieceType(F8) == NONE &&
			getPieceType(G8) == NONE)
		{
			if (!isSqAttacked(E8, WHITE) &&
				!isSqAttacked(F8, WHITE) &&
				!isSqAttacked(G8, WHITE))
			{
				addQuietMove(M_MOVE(E8, G8, NONE, NONE, CAS_FLAG));
			}
		}
		if (b_queen_castle &&
			getPieceType(D8) == NONE &&
			getPieceType(C8) == NONE &&
			getPieceType(B8) == NONE)
		{
			if (!isSqAttacked(E8, WHITE) &&
				!isSqAttacked(D8, WHITE) &&
				!isSqAttacked(C8, WHITE))
			{
				addQuietMove(M_MOVE(E8, C8, NONE, NONE, CAS_FLAG));
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

void Board::deletePiece(const int sq)
{
	int piece = getPieceType(sq);
	U64 bb = ((1ULL << sq) & getPieceBitboard(piece));
	setPieceBitboard(piece, bb);
}

void Board::addPiece(const int sq, const int piece_type)
{
	U64 bb = (getPieceBitboard(piece_type) | (1ULL << sq));
	setPieceBitboard(piece_type, bb);
}

void Board::movePiece(const int from, const int to)
{
	int piece_type = getPieceType(from);
	U64 new_bb = getPieceBitboard(piece_type);
	new_bb = new_bb & (~(1ULL << from));
	new_bb = new_bb | (1ULL << to);
	setPieceBitboard(piece_type, new_bb);
}

// returns false if illegal move - king is in check after move
bool Board::makeMove(int move)
{
	int from = FROMSQ(move);
	int to = TOSQ(move);

	if (move & EP_FLAG)
	{
		if (side_to_move == WHITE)
		{
			deletePiece(to - 8); 
		}
		else
		{
			deletePiece(to + 8);
		}
	}
	else if (move & CAS_FLAG)
	{
		switch(to)
		{
			case C1:
				movePiece(A1, D1);
			break;
			case C8:
				movePiece(A8, D8);
			break;
			case G1:
				movePiece(H1, F1);
			break;
			case G8:
				movePiece(H8, F8);
			break;
			default:
				std::cout << "ERROR IN MAKEMOVE CASTLING\n";
			break;
		}
	}

	history[game_ply].move = move;
	history[game_ply].w_king_castle = w_king_castle;
	history[game_ply].w_queen_castle = w_queen_castle;
	history[game_ply].b_king_castle = b_king_castle;
	history[game_ply].b_queen_castle = b_queen_castle;
	history[game_ply].ep_square = ep_square;

	int captured = CAP_PIECE(move);
	if (captured != NONE)
	{
		deletePiece(to);
	}

	game_ply++;
	
	// need to do a search_ply++

	int moving_piece = getPieceType(from);
	if (moving_piece == wP && (move & PS_FLAG))
	{
		ep_square = from + 8;
	}
	else if (moving_piece == bP && (move & PS_FLAG))
	{
		ep_square = from - 8;
	}
	else
	{
		ep_square = -1;
	}

	movePiece(from, to);

	int promotion = PROM_PIECE(move);
	if (promotion != NONE)
	{
		deletePiece(to);
		addPiece(to, promotion);
	}
	

	// check if the king is under attack as result of move
	int i = 0;
	for (i = 0; i < 64; i++)
	{
		if (side_to_move == WHITE)
		{
			if (1ULL << i == getPieceBitboard(wK))
			{
				break;
			}
		}
		else
		{
			if (1ULL << i == getPieceBitboard(bK))
			{
				break;
			}
		}
	}
	
	side_to_move ^= 1;

	if (isSqAttacked(i, side_to_move))
	{
		undoMove();
		return false;
	};
	return true;
}

void Board::undoMove()
{
	game_ply--;

	int move = history[game_ply].move;
	int from = FROMSQ(move);
	int to = TOSQ(move);

	ep_square = history[game_ply].ep_square;
	w_king_castle = history[game_ply].w_king_castle;
	w_queen_castle = history[game_ply].w_queen_castle;
	b_king_castle = history[game_ply].b_king_castle;
	b_queen_castle = history[game_ply].b_queen_castle;

	side_to_move ^= 1;

	if (move & EP_FLAG)
	{
		if (side_to_move == WHITE)
		{
			addPiece(to - 8, bP);
		}
		else
		{
			addPiece(to + 8, wP);
		}
	}
	if (move & CAS_FLAG)
	{
		switch(to)
		{
			case C1:
				movePiece(D1, A1);
				break;
			case C8:
				movePiece(D8, A8);
				break;
			case G1:
				movePiece(F1, H1);
				break;
			case G8:
				movePiece(F8, H8);
				break;
			default:
				break;
		}
	}

	movePiece(to, from);

	int captured = CAP_PIECE(move);
	if (captured != NONE)
	{
		addPiece(to, captured);
	}

	if (PROM_PIECE(move) != NONE)
	{
		deletePiece(from);
		if (side_to_move == WHITE)
		{
			addPiece(from, wP);
		}
		else
		{
			addPiece(from, bP);
		}
	}
}