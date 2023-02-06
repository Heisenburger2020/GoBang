#include "Machine.h"

/*
局面评估：
对于每个点赋予一个分值：对方得分加上自己得分
整个局面得分为4个得分最大的点之和
*/

// 需要修改平局情形
Decision::Decision() {
    x = -1;
    y = -1;
    score = -1;
}

Decision::Decision(int score_in, int x_in, int y_in) {
    score = score_in;
    x = x_in;
    y = y_in;
}

Decision::Decision(bool is_min) {
    x = -1;
    y = -1;
    if (is_min) {
        score = MIN_SCORE;
    } else {
        score = MAX_SCORE;
    }
}

Machine::Machine() {
}

Decision Machine::MinDecision(ChessBoard chess_board, int x, int y, int layer, char color) {
    // 如果机器方有一个color颜色的子下到x y，那么返回最终层得分
    // color 机器颜色
    // 玩家回合
    chess_board.AddChess(x, y, color);
    Decision res(false);
    UtilityInfo info = chess_board.EvaluateBoardUtility(3 - color);

    if (Judge::IsGameWinNoChess(chess_board, {info.pts_[0].x_, info.pts_[0].y_}, 3 - color)) {
        return {-1 * Consts::five_, x, y};
    }

    for (int i = 0; i <= info.cur_id_; i++) {
        if (3 - color == 1 && Judge::IsForbiddenHand(&chess_board, {info.pts_[i].x_, info.pts_[i].y_})) continue;
        Decision t = MaxDecision(chess_board, info.pts_[i].x_, info.pts_[i].y_, layer + 1, 3 - color);
        if (t.score < res.score) {
            res = {t.score, x, y};
        }
    }

    return res;
}

Decision Machine::MaxDecision(ChessBoard chess_board, int x, int y, int layer, char color) {
    // 如果玩家方有一个color颜色的子下到x y，那么返回最终层得分
    // color 玩家颜色
    // 机器回合
    chess_board.AddChess(x, y, color);
    Decision res(true);
    UtilityInfo info = chess_board.EvaluateBoardUtility(3 - color);

    if (layer >= SEARCH_LAYER) {
        return {info.score_, x, y};
    }

    if (Judge::IsGameWinNoChess(chess_board, {info.pts_[0].x_, info.pts_[0].y_}, 3 - color)) {
        return {Consts::five_, x, y};
    }

    for (int i = 0; i <= info.cur_id_; i++) {
        if (3 - color == 1 && Judge::IsForbiddenHand(&chess_board, {info.pts_[i].x_, info.pts_[i].y_})) continue;
        Decision t = MinDecision(chess_board, info.pts_[i].x_, info.pts_[i].y_, layer, 3 - color);
        if (t.score > res.score) {
            res = {t.score, x, y};
        }
    }
    return res;
}

void Machine::PlayChess(ChessBoard &chess_board, int num_round) {
    char color = 3 - chess_board.cur_color_; // 改下的子的颜色
    if (num_round == 0 && !chess_board.chesses_[7][7]) {
        chess_board.AddChess(7, 7, color);
        return;
    }
    Decision res(true);
    UtilityInfo info = chess_board.EvaluateBoardUtility(color);
    for (int i = 0; i <= info.cur_id_; i++) {
        if (color == 1 && Judge::IsForbiddenHand(&chess_board, {info.pts_[i].x_, info.pts_[i].y_})) continue;
        Decision t = MinDecision(chess_board, info.pts_[i].x_, info.pts_[i].y_, 0, color);
        if (t.score > res.score) {
            res = t;
        }
    }
    std::cout << res.x << ' ' << res.y << std::endl;
    chess_board.AddChess(res.x, res.y, color);
}
