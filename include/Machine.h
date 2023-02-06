#pragma once

#include <iostream>

#include "Player.h"
#include "Consts.h"
#include "Judge.h"

#define MAX_SCORE 0X3f3f3f3f
#define MIN_SCORE -MAX_SCORE

#define SEARCH_LAYER 2

struct Decision {
    int score;
    int x;
    int y;

	Decision();
    Decision(int score, int x, int y);
    Decision(bool is_min);
};

class Machine : public Player
{
public:
	
	Machine();

	virtual void PlayChess(ChessBoard &chess_board, int num_round);

	Decision MinDecision(ChessBoard chess_board, int x, int y, int layer, char color);
    Decision MaxDecision(ChessBoard chess_board, int x, int y, int layer, char color);
};

