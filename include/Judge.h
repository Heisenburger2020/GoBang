#pragma once

#include <utility>
#include <algorithm>
#include <iostream>

#include "ChessBoard.h"

struct PointInfo {
    int num_of_three;
    int num_of_four;
    int num_of_length;

    PointInfo() {
        num_of_three = 0;
        num_of_four = 0;
        num_of_length = 0;
    }
};

class ChessBoard;

class Judge {
public:
    Judge();

    static PII direction[8];

    static bool IsForbiddenHand(ChessBoard *chess_board, PII last_update);
    static PointInfo GetPointInfo(ChessBoard *chess_board);
    static bool IsGameWin(ChessBoard *chess_board);

    static bool IsForbiddenHand(ChessBoard chess_board);
    static PointInfo GetPointInfo(ChessBoard chess_board);
    static bool IsGameWin(ChessBoard chess_board);
    static bool IsGameWinNoChess(ChessBoard chess_board, PII last_update, char color);
};
