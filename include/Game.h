#pragma once

#include <cstdio>
#include <iostream>
#include <ctime>

#include "ChessBoard.h"
#include "Player.h"
#include "Human.h"
#include "Machine.h"
#include "Judge.h"

class Game
{
public:
	Game();
private:
	bool is_player_black_;
	int game_mode_; // 1 ���ˣ� 2 �˻�
	int num_round_;

	ChessBoard chess_board_;

	Player* black_;
	Player* white_;
public:
	void InitGame();
	void SelectMode();
	void SelectFirstHand();
	void StartGame();
	void EndGame();
	void ReGame();
	void GameOver(char color);

	void HumanHumanMatch();
	void HumanMachineMatch();
};

