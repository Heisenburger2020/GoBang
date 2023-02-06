#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

#include "ChessBoard.h"
#include "Judge.h"

int ChessBoard::init_score_[][15] = {
    {2, 15, 26, 35, 42, 47, 50, 51, 50, 47, 42, 35, 26, 15, 2},
    {15, 28, 39, 48, 55, 60, 63, 64, 63, 60, 55, 48, 39, 28, 15},
    {26, 39, 50, 59, 66, 71, 74, 75, 74, 71, 66, 59, 50, 39, 26},
    {35, 48, 59, 68, 75, 80, 83, 84, 83, 80, 75, 68, 59, 48, 35},
    {42, 55, 66, 75, 82, 87, 90, 91, 90, 87, 82, 75, 66, 55, 42},
    {47, 60, 71, 80, 87, 92, 95, 96, 95, 92, 87, 80, 71, 60, 47},
    {50, 63, 74, 83, 90, 95, 98, 99, 98, 95, 90, 83, 74, 63, 50},
    {51, 64, 75, 84, 91, 96, 99, 100, 99, 96, 91, 84, 75, 64, 51},
    {50, 63, 74, 83, 90, 95, 98, 99, 98, 95, 90, 83, 74, 63, 50},
    {47, 60, 71, 80, 87, 92, 95, 96, 95, 92, 87, 80, 71, 60, 47},
    {42, 55, 66, 75, 82, 87, 90, 91, 90, 87, 82, 75, 66, 55, 42},
    {35, 48, 59, 68, 75, 80, 83, 84, 83, 80, 75, 68, 59, 48, 35},
    {26, 39, 50, 59, 66, 71, 74, 75, 74, 71, 66, 59, 50, 39, 26},
    {15, 28, 39, 48, 55, 60, 63, 64, 63, 60, 55, 48, 39, 28, 15},
    {2, 15, 26, 35, 42, 47, 50, 51, 50, 47, 42, 35, 26, 15, 2}};

void ChessBoard::InitScore() {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            init_score_[i][j] *= INIT_SCORE;
        }
    }
}

ChessBoard::ChessBoard() {
    pos_last_black_ = {-1, -1};
    pos_last_white_ = {-1, -1};
    cur_color_ = 0;
    memset(chesses_, 0, sizeof chesses_);
    memcpy(black_socre_, init_score_, sizeof black_socre_);
    memcpy(white_socre_, init_score_, sizeof black_socre_);
}

ChessBoard::ChessBoard(ChessBoard* original) {
    memcpy(chesses_, original->chesses_, sizeof chesses_);
}

void ChessBoard::InitChessBoard() {
    pos_last_black_ = {-1, -1};
    pos_last_white_ = {-1, -1};
    cur_color_ = 2;
    memset(chesses_, 0, sizeof chesses_);
    memcpy(black_socre_, init_score_, sizeof black_socre_);
    memcpy(white_socre_, init_score_, sizeof black_socre_);
}

void ChessBoard::DrawChessBoard() {
    printf("\n\t五子棋(黑色方:● 白色方:○)\n\n");

    // 第一行
    // 左上角特殊符号
    if (!chesses_[0][0]) {
        printf("\t15┏ ");
    } else {
        DrawChess(0, 0, 15);
    }
    // 第一行特殊符号
    for (int y = 1, x = 0; y < 14; y++) {
        if (!chesses_[x][y]) {
            printf("┯ ");
        } else {
            DrawChess(x, y);
        }
    }
    // 右上角特殊符号
    if (!chesses_[0][14]) {
        printf("┓\n");
    } else {
        DrawChess(0, 14);
        printf("\n");
    }

    // 中间
    for (int x = 1; x < 14; x++) {
        // 左一列
        if (!chesses_[x][0]) {
            printf("\t%2d┠ ", 15 - x);
        } else {
            DrawChess(x, 0, 15 - x);
        }
        // 中间列
        for (int y = 1; y < 14; y++) {
            if (!chesses_[x][y]) {
                printf("┼ ");
            } else {
                DrawChess(x, y);
            }
        }
        // 右一列
        if (!chesses_[x][14]) {
            printf("┨\n");
        } else {
            DrawChess(x, 14);
            printf("\n");
        }
    }

    // 最后一行
    // 最左一列
    if (!chesses_[14][0]) {
        printf("\t 1┗ ");
    } else {
        DrawChess(14, 0, 1);
    }
    // 中间
    for (int y = 1; y < 14; y++) {
        if (!chesses_[14][y]) {
            printf("┷ ");
        } else {
            DrawChess(14, y);
        }
    }
    // 最右一列
    if (!chesses_[14][14]) {
        printf("┛\n");
    } else {
        DrawChess(14, 14);
        printf("\n");
    }

    printf("\t ");
    for (char col_label = 'A'; col_label <= 'O'; col_label++) {
        printf(" %c", col_label);
    }
    printf("\n");
}

void ChessBoard::AddChess(int x, int y, char color, bool is_HumanMachine) {
    chesses_[x][y] = color;
    if (color == 1) {
        pos_last_black_ = {x, y};
    } else if (color == 2) {
        pos_last_white_ = {x, y};
    }
    cur_color_ = color;
    if (is_HumanMachine) UtilityAssess(x, y);
}

bool ChessBoard::IsVacant(int x, int y) {
    if (x < 0 || x > 14 || y < 0 || y > 14) return false;
    return !chesses_[x][y];
}

bool ChessBoard::IsInBoard(int x, int y) {
    if (x < 0 || x > 14 || y < 0 || y > 14) return false;
    return true;
}

PII ChessBoard::LastUpdate() {
    if (cur_color_ == 1)
        return pos_last_black_;
    else if (cur_color_ == 2)
        return pos_last_white_;
}

void ChessBoard::DrawChess(int x, int y, int col) {
    if (col) {
        if (chesses_[x][y] == 1) {
            if (pos_last_black_.first == x && pos_last_black_.second == y)
                printf("\t%2d▲", col);
            else
                printf("\t%2d●", col);
        } else if (chesses_[x][y] == 2) {
            if (pos_last_white_.first == x && pos_last_white_.second == y)
                printf("\t%2d△", col);
            else
                printf("\t%2d○", col);
        }
    } else {
        if (chesses_[x][y] == 1) {
            if (pos_last_black_.first == x && pos_last_black_.second == y)
                printf("▲");
            else
                printf("●");
        } else if (chesses_[x][y] == 2) {
            if (pos_last_white_.first == x && pos_last_white_.second == y)
                printf("△");
            else
                printf("○");
        }
    }
}

TwoDimArray ChessBoard::ScoreSameColor(char color) {
    if (color == 1)
        return black_socre_;
    else
        return white_socre_;
}

TwoDimArray ChessBoard::ScoreDiffColor(char color) {
    if (color == 2)
        return black_socre_;
    else
        return white_socre_;
}

void ChessBoard::UtilityAssess(int x, int y) {
    // 如今有一子刚下载(x,y)位置

    TwoDimArray score_same_color = ScoreSameColor(cur_color_);
    TwoDimArray score_diff_color = ScoreDiffColor(cur_color_);
    char opposite_color = 3 - cur_color_;

    // 给相同颜色
    if (cur_color_ == 1) {
        // 如果是黑色棋子目前
        for (int i = x - 2; i <= x + 2; i++) {
            for (int j = y - 2; j <= y + 2; j++) {
                if (!IsVacant(i, j)) continue;
                black_socre_[i][j] += CONVO_SCORE;
            }
        }
    } else {
        // 如果是白色棋子目前
        for (int i = x - 2; i <= x + 2; i++) {
            for (int j = y - 2; j <= y + 2; j++) {
                if (!IsVacant(i, j)) continue;
                white_socre_[i][j] += CONVO_SCORE;
            }
        }
    }

    for (int dir_id = 0; dir_id < 4; dir_id++) {
        PII tmp = {x, y};
        int cnt[2][2];         // 0 通， 1 不通
        int cnt_suppose[2][2]; // 0 通， 1 不通
        int cnt_continum = 1;  // 0 连，1 suppose; 0 通，1 不通
        bool is_block[2][2];   // 方向， 是否假设
        memset(cnt, 0, sizeof cnt);
        memset(cnt_suppose, 0, sizeof cnt_suppose);
        memset(is_block, 0, sizeof is_block);

        while (chesses_[tmp.first + Consts::direction[dir_id].first][tmp.second + Consts::direction[dir_id].second] == cur_color_) {
            tmp.first += Consts::direction[dir_id].first;
            tmp.second += Consts::direction[dir_id].second;
            cnt_continum++;
        }

        tmp.first += Consts::direction[dir_id].first;
        tmp.second += Consts::direction[dir_id].second;

        if (!chesses_[tmp.first][tmp.second]) {
            // 如果是空的
            cnt[0][0] = cnt_continum;
            while (chesses_[tmp.first + Consts::direction[dir_id].first][tmp.second + Consts::direction[dir_id].second] == cur_color_) {
                tmp.first += Consts::direction[dir_id].first;
                tmp.second += Consts::direction[dir_id].second;
                cnt_continum++;
            }
            if (!chesses_[tmp.first][tmp.second]) {
                cnt_suppose[0][0] = cnt_continum + 1;
            } else {
                cnt_suppose[0][1] = cnt_continum;
                is_block[0][1] = true;
            }
        } else {
            is_block[0][0] = true;
            is_block[0][1] = true;
            cnt[0][1] = cnt_continum;
        }

        // 右边
        tmp = {x, y};
        cnt_continum = 0;
        while (chesses_[tmp.first - Consts::direction[dir_id].first][tmp.second - Consts::direction[dir_id].second] == cur_color_) {
            tmp.first -= Consts::direction[dir_id].first;
            tmp.second -= Consts::direction[dir_id].second;
            cnt_continum++;
        }

        tmp.first -= Consts::direction[dir_id].first;
        tmp.second -= Consts::direction[dir_id].second;

        if (!chesses_[tmp.first][tmp.second]) {
            // 如果是空的
            cnt[1][0] = cnt_continum;
            while (chesses_[tmp.first - Consts::direction[dir_id].first][tmp.second - Consts::direction[dir_id].second] == cur_color_) {
                tmp.first -= Consts::direction[dir_id].first;
                tmp.second -= Consts::direction[dir_id].second;
                cnt_continum++;
            }
            if (!chesses_[tmp.first][tmp.second]) {
                cnt_suppose[1][0] = cnt_continum + 1;
            } else {
                cnt_suppose[1][1] = cnt_continum;
                is_block[1][1] = true;
            }
        } else {
            is_block[1][0] = true;
            is_block[1][1] = true;
            cnt[1][1] = cnt_continum;
        }

        if (!is_block[0][0] && !is_block[1][0]) {
            // 两个方向都没有被堵
            int len = cnt[0][0] + cnt[1][0] + 1;
            if (len <= 5) {
                score_same_color[x + cnt[0][0] * Consts::direction[dir_id].first][y + cnt[0][0] * Consts::direction[dir_id].second] += Consts::live_[len];
                score_same_color[x - (cnt[1][0] + 1) * Consts::direction[dir_id].first][y - (cnt[1][0] + 1) * Consts::direction[dir_id].second] += Consts::live_[len];
            }
            // 前进方向跳过一个子
            int len_suppose1 = cnt_suppose[0][0] + cnt[1][0];
            if (len_suppose1 > len && len_suppose1 <= 5) {
                if (!is_block[0][1]) {
                    // 没有被挡住
                    score_same_color[x + cnt[0][0] * Consts::direction[dir_id].first][y + cnt[0][0] * Consts::direction[dir_id].second] += Consts::live_[len_suppose1];
                } else {
                    // 被挡住了
                    score_same_color[x + cnt[0][0] * Consts::direction[dir_id].first][y + cnt[0][0] * Consts::direction[dir_id].second] += Consts::blocked_[len_suppose1];
                }
            }
            // 后退方向跳过一个子
            int len_suppose2 = cnt_suppose[1][0] + cnt[0][0];
            if (len_suppose2 > len && len_suppose2 <= 5) {
                if (!is_block[1][1]) {
                    // 没有被挡住
                    score_same_color[x - (cnt[1][0] + 1) * Consts::direction[dir_id].first][y + (cnt[1][0] + 1) * Consts::direction[dir_id].second] += Consts::live_[len_suppose1];
                } else {
                    // 被挡住了
                    score_same_color[x - (cnt[1][0] + 1) * Consts::direction[dir_id].first][y + (cnt[0][0] + 1) * Consts::direction[dir_id].second] += Consts::blocked_[len_suppose1];
                }
            }

        } else if (is_block[0][0] && !is_block[1][0]) {
            // 前进方向被堵
            int len = cnt[0][1] + cnt[1][0] + 1;
            if (len <= 5) {
                score_same_color[x - (cnt[1][0] + 1) * Consts::direction[dir_id].first][y - (cnt[1][0] + 1) * Consts::direction[dir_id].second] += Consts::blocked_[len];
            }

            // 后退方向跳过一个子
            int len_suppose2 = cnt_suppose[1][0] + cnt[0][0];
            if (len_suppose2 > len && len_suppose2 <= 5) {
                if (!is_block[1][1]) {
                    // 没有被挡住
                    score_same_color[x - (cnt[1][0] + 1) * Consts::direction[dir_id].first][y + (cnt[1][0] + 1) * Consts::direction[dir_id].second] += Consts::live_[len_suppose2];
                } 
            }
        } else if (!is_block[0][0] && is_block[1][0]) {
            // 后退方向被堵
            int len = cnt[0][0] + cnt[1][1] + 1;
            if (len <= 5) {
                score_same_color[x + cnt[0][0] * Consts::direction[dir_id].first][y + cnt[0][0] * Consts::direction[dir_id].second] += Consts::blocked_[len];
            }

            // 前进方向跳过一个子
            int len_suppose1 = cnt_suppose[0][0] + cnt[1][0];
            if (len_suppose1 > len && len_suppose1 <= 5) {
                if (!is_block[0][1]) {
                    // 没有被挡住
                    score_same_color[x + cnt[0][0] * Consts::direction[dir_id].first][y + cnt[0][0] * Consts::direction[dir_id].second] += Consts::live_[len_suppose1];
                }
            }
        } 
    }

    // 其次查看对不同颜色的棋子局面的影响
    for (int dir_id = 0; dir_id < 4; dir_id++) {
        PII tmp = {x, y};
        int cnt[2][2];         // 0 通， 1 不通
        int cnt_continum = 0;  // 0 连，1 suppose; 0 通，1 不通
        bool is_block[2];   // 方向， 是否假设
        memset(cnt, 0, sizeof cnt);
        memset(is_block, 0, sizeof is_block);

        while (chesses_[tmp.first + Consts::direction[dir_id].first][tmp.second + Consts::direction[dir_id].second] == opposite_color) {
            tmp.first += Consts::direction[dir_id].first;
            tmp.second += Consts::direction[dir_id].second;
            cnt_continum++;
        }

        tmp.first += Consts::direction[dir_id].first;
        tmp.second += Consts::direction[dir_id].second;

        if (!chesses_[tmp.first][tmp.second]) {
            // 如果是空的
            cnt[0][0] = cnt_continum;
        } else {
            is_block[0] = true;
            cnt[0][1] = cnt_continum;
        }

        // 右边
        tmp = {x, y};
        cnt_continum = 0;
        while (chesses_[tmp.first - Consts::direction[dir_id].first][tmp.second - Consts::direction[dir_id].second] == opposite_color) {
            tmp.first -= Consts::direction[dir_id].first;
            tmp.second -= Consts::direction[dir_id].second;
            cnt_continum++;
        }

        tmp.first -= Consts::direction[dir_id].first;
        tmp.second -= Consts::direction[dir_id].second;

        if (!chesses_[tmp.first][tmp.second]) {
            // 如果是空的
            cnt[1][0] = cnt_continum;
        } else {
            is_block[1] = true;
            cnt[1][1] = cnt_continum;
        }

        if (!is_block[0]) {
            // 前进方向没有被堵
            score_diff_color[x + (cnt[0][0] + 1) * Consts::direction[dir_id].first][y + (cnt[0][0] + 1) * Consts::direction[dir_id].second] -= Consts::blocked_diff_[cnt[0][0]];
        }

        if (!is_block[1]) {
            // 后退方向没有被堵
            score_diff_color[x - (cnt[0][0] + 1) * Consts::direction[dir_id].first][y - (cnt[0][0] + 1) * Consts::direction[dir_id].second] -= Consts::blocked_diff_[cnt[1][0]];
        }
    }
}

UtilityInfo ChessBoard::EvaluateBoardUtility(char color) {
    UtilityInfo res;
    PseudoHeap self, opponent;
    TwoDimArray score_same_color = ScoreSameColor(color);
    TwoDimArray score_diff_color = ScoreDiffColor(color);

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (chesses_[i][j] || Judge::IsForbiddenHand(this, {i, j})) continue;
            int t = UTILITY_ALPHA * score_same_color[i][j] + UTILITY_BETA * score_diff_color[i][j];
            self.AddScore(score_same_color[i][j], i, j);
            opponent.AddScore(score_diff_color[i][j], i, j);

            if (res.cur_id_ != -1) {
                if (t > res.pts_[res.cur_id_].score_) {
                    if (res.cur_id_ < 3) {
                        res.pts_[++res.cur_id_] = {t, i, j};
                        std::sort(res.pts_, res.pts_ + 4, PointScore::cmp);
                    } else {
                        res.pts_[res.cur_id_] = {t, i, j};
                        std::sort(res.pts_, res.pts_ + 4, PointScore::cmp);
                    }
                }
            } else {
                res.pts_[++res.cur_id_] = {t, i, j};
            }
        }
    }

    res.CountScore(self, opponent);
    return res;
}
