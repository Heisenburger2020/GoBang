#pragma once

#include "Player.h"
#include "Consts.h"

class Human : public Player
{
public:
	Human();

	virtual void PlayChess(ChessBoard &chess_board, int num_round);

	static int col_int2int(char id);
	static int row_char2int(int id);
};

