#include "Player.h"

Player::Player() {
	
}

Player::Player(char color) {
	color_ = color;
}

void Player::AddChess(ChessBoard chess_board, int x, int y) {
	chess_board.AddChess(x, y, color_);
}

void Player::PlayChess(ChessBoard &chess_board, int num_round) {
	printf("Error!");
    exit(10);
}
