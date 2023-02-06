#pragma once
#include <string>

#include "ChessBoard.h"


class Player
{
public:
	char color_;
	std::string player_name_;
	std::string chess_shape_;

	Player();
	Player(char color);

	virtual void PlayChess(ChessBoard &chess_board, int num_round);

	void AddChess(ChessBoard chess_board, int x, int y);
};

