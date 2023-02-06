#include "Judge.h"
#include "ChessBoard.h"

Judge::Judge() {
}

PII Judge::direction[8] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

PointInfo Judge::GetPointInfo(ChessBoard *chess_board) {
    PointInfo info;
    PII last_update = chess_board->LastUpdate();
    for (int dir_id = 0; dir_id < 4; dir_id++) {
        int temp_x = last_update.first, temp_y = last_update.second;
        // ͳ��ǰ��
        int cnt_continuum = 1;
        static int cnt[2][2];         // 0�� 1��  0ͨ 1��ͨ
        static int cnt_suppose[2][2]; // 0�� 1�� ��������һ����
        static bool is_block[2][2];   // 0ǰ 1�� 0 ������ 1 ����
        memset(cnt, 0, sizeof cnt);
        memset(cnt_suppose, 0, sizeof cnt_suppose);
        memset(is_block, 0, sizeof is_block);
        char color = chess_board->cur_color_;
        while (chess_board->IsInBoard(temp_x + direction[dir_id].first, temp_y + direction[dir_id].second)
               && chess_board->chesses_[temp_x + direction[dir_id].first][temp_y + direction[dir_id].second] == color) {
            temp_x += direction[dir_id].first;
            temp_y += direction[dir_id].second;
            cnt_continuum++;
        }

        if (chess_board->IsVacant(temp_x + direction[dir_id].first, temp_y + direction[dir_id].second)) {
            cnt[0][0] = cnt_continuum;
            int cnt_s = cnt_continuum + 1;

            temp_x += direction[dir_id].first;
            temp_y += direction[dir_id].second;

            while (chess_board->IsInBoard(temp_x + direction[dir_id].first, temp_y + direction[dir_id].second) && chess_board->chesses_[temp_x + direction[dir_id].first][temp_y + direction[dir_id].second] == color) {
                temp_x += direction[dir_id].first;
                temp_y += direction[dir_id].second;
                cnt_s++;
            }

            if (chess_board->IsVacant(temp_x + direction[dir_id].first, temp_y + direction[dir_id].second))
                cnt_suppose[0][0] = cnt_s;
            else {
                cnt_suppose[0][1] = cnt_s;
                is_block[0][1] = true;
            }

        } else {
            cnt[0][1] = cnt_continuum;
            is_block[0][0] = true;
            is_block[0][1] = true;
        }
        // ͳ�ƺ���
        cnt_continuum = 0;
        temp_x = last_update.first, temp_y = last_update.second;
        while (chess_board->IsInBoard(temp_x - direction[dir_id].first, temp_y - direction[dir_id].second) && chess_board->chesses_[temp_x - direction[dir_id].first][temp_y - direction[dir_id].second] == color) {
            temp_x -= direction[dir_id].first;
            temp_y -= direction[dir_id].second;
            cnt_continuum++;
        }

        if (chess_board->IsVacant(temp_x - direction[dir_id].first, temp_y - direction[dir_id].second)) {
            cnt[1][0] = cnt_continuum;
            int cnt_s = cnt_continuum + 1;

            temp_x -= direction[dir_id].first;
            temp_y -= direction[dir_id].second;

            while (chess_board->IsInBoard(temp_x - direction[dir_id].first, temp_y - direction[dir_id].second) && chess_board->chesses_[temp_x - direction[dir_id].first][temp_y - direction[dir_id].second] == color) {
                temp_x -= direction[dir_id].first;
                temp_y -= direction[dir_id].second;
                cnt_s++;
            }
            if (chess_board->IsVacant(temp_x - direction[dir_id].first, temp_y - direction[dir_id].second))
                cnt_suppose[1][0] = cnt_s;
            else {
                cnt_suppose[1][1] = cnt_s;
                is_block[1][1] = true;
            }

        } else {
            cnt[1][1] = cnt_continuum;
            is_block[1][0] = true;
            is_block[1][1] = true;
        }

        // �жϻ���
        if (!is_block[0][1] && !is_block[1][0] && cnt_suppose[0][0] + cnt[1][0] >= 4) {
            if (++info.num_of_three >= 2) return info;
        } else if (!is_block[1][1] && !is_block[0][0] && cnt_suppose[1][0] + cnt[0][0] >= 4) {
            if (++info.num_of_three >= 2) return info;
        }

        if (!is_block[0][1] && !is_block[1][1] && cnt_suppose[0][0] - cnt[0][0] > 1 && cnt_suppose[1][0] - cnt[1][0] > 1) {
            if (cnt_suppose[0][0] + cnt[1][0] >= 4 && cnt_suppose[1][0] + cnt[0][0] >= 4) {
                if (++info.num_of_three >= 2) return info;
            }
        }

        // �жϻ��ĳ���
        // ��֤���������ִ��ڵ��ڱ���
        cnt[0][0] = std::max(cnt[0][0], cnt[0][1]);
        cnt[1][0] = std::max(cnt[1][0], cnt[1][1]);
        cnt_suppose[0][0] = std::max(cnt_suppose[0][0], cnt_suppose[0][1]);
        cnt_suppose[1][0] = std::max(cnt_suppose[1][0], cnt_suppose[0][1]);

        if ((!is_block[0][1] || !is_block[1][0]) && cnt_suppose[0][0] + cnt[1][0] >= 5) { // ǰsuppose ��suppose
            if (++info.num_of_four >= 2) return info;
        } else if ((!is_block[1][1] || !is_block[0][0]) && cnt_suppose[1][0] + cnt[0][0] >= 5) { // ��suppose ǰ��suppose
            if (++info.num_of_four >= 2) return info;
        }

        if (!is_block[0][0] && !is_block[1][0] && cnt_suppose[0][0] - cnt[0][0] > 1 && cnt_suppose[1][0] - cnt[1][0] > 1) {
            if (cnt_suppose[0][0] + cnt[1][0] >= 5 && cnt_suppose[1][0] + cnt[0][0] >= 5) {
                if (++info.num_of_four >= 2) return info;
            } else if (cnt_suppose[0][1] + cnt[1][1] >= 5 && cnt_suppose[1][0] + cnt[0][0] >= 5) {
                if (++info.num_of_four >= 2) return info;
            }
        }

        // �жϳ���
        if (cnt[1][1] + cnt[0][1] > 5) {
            info.num_of_length++;
            return info;
        }
    }
    return info;
}

bool Judge::IsGameWin(ChessBoard *chess_board) {
    PII last_update = chess_board->LastUpdate();
    int color_of_chess = chess_board->cur_color_;
    for (int dir_id = 0; dir_id < 4; dir_id++) {
        int cnt_continuum = 1;
        int temp_x = last_update.first, temp_y = last_update.second;
        while (chess_board->IsInBoard(temp_x + direction[dir_id].first, temp_y + direction[dir_id].second) && chess_board->chesses_[temp_x + direction[dir_id].first][temp_y + direction[dir_id].second] == color_of_chess) {
            temp_x += direction[dir_id].first;
            temp_y += direction[dir_id].second;
            cnt_continuum++;
        }
        temp_x = last_update.first, temp_y = last_update.second;
        while (chess_board->IsInBoard(temp_x - direction[dir_id].first, temp_y - direction[dir_id].second) && chess_board->chesses_[temp_x - direction[dir_id].first][temp_y - direction[dir_id].second] == color_of_chess) {
            temp_x -= direction[dir_id].first;
            temp_y -= direction[dir_id].second;
            cnt_continuum++;
        }
        if (cnt_continuum == 5 && color_of_chess == 1) return true;
        if (cnt_continuum >= 5 && color_of_chess == 2) return true;
    }
    return false;
}

bool Judge::IsForbiddenHand(ChessBoard *chess_board_t, PII last_update) {
    ChessBoard *chess_board = new ChessBoard(chess_board_t);
    if (last_update.first < 0 || last_update.first >= 15 || last_update.second < 0 || last_update.second >= 15) return true;
    if (IsGameWin(chess_board)) return false;
    chess_board->chesses_[last_update.first][last_update.second] = chess_board->cur_color_;

    // ����Ǻ��壬�ܽ�������
    if (chess_board->cur_color_) {
        PointInfo info = GetPointInfo(chess_board);

        if (info.num_of_three >= 2 || info.num_of_four >= 2 || info.num_of_length > 0) {
            return true;
        }
    }
    return false;
}

PointInfo Judge::GetPointInfo(ChessBoard chess_board) {
    PointInfo info;
    PII last_update = chess_board.LastUpdate();
    for (int dir_id = 0; dir_id < 4; dir_id++) {
        int temp_x = last_update.first, temp_y = last_update.second;
        // ͳ��ǰ��
        int cnt_continuum = 1;
        static int cnt[2][2];         // 0�� 1��  0ͨ 1��ͨ
        static int cnt_suppose[2][2]; // 0�� 1�� ��������һ����
        static bool is_block[2][2];   // 0ǰ 1�� 0 ������ 1 ����
        memset(cnt, 0, sizeof cnt);
        memset(cnt_suppose, 0, sizeof cnt_suppose);
        memset(is_block, 0, sizeof is_block);
        char color = chess_board.cur_color_;
        while (chess_board.IsInBoard(temp_x + direction[dir_id].first, temp_y + direction[dir_id].second)
               && chess_board.chesses_[temp_x + direction[dir_id].first][temp_y + direction[dir_id].second] == color) {
            temp_x += direction[dir_id].first;
            temp_y += direction[dir_id].second;
            cnt_continuum++;
        }

        if (chess_board.IsVacant(temp_x + direction[dir_id].first, temp_y + direction[dir_id].second)) {
            cnt[0][0] = cnt_continuum;
            int cnt_s = cnt_continuum + 1;

            temp_x += direction[dir_id].first;
            temp_y += direction[dir_id].second;

            while (chess_board.IsInBoard(temp_x + direction[dir_id].first, temp_y + direction[dir_id].second) && chess_board.chesses_[temp_x + direction[dir_id].first][temp_y + direction[dir_id].second] == color) {
                temp_x += direction[dir_id].first;
                temp_y += direction[dir_id].second;
                cnt_s++;
            }

            if (chess_board.IsVacant(temp_x + direction[dir_id].first, temp_y + direction[dir_id].second))
                cnt_suppose[0][0] = cnt_s;
            else {
                cnt_suppose[0][1] = cnt_s;
                is_block[0][1] = true;
            }

        } else {
            cnt[0][1] = cnt_continuum;
            is_block[0][0] = true;
            is_block[0][1] = true;
        }
        // ͳ�ƺ���
        cnt_continuum = 0;
        temp_x = last_update.first, temp_y = last_update.second;
        while (chess_board.IsInBoard(temp_x - direction[dir_id].first, temp_y - direction[dir_id].second) && chess_board.chesses_[temp_x - direction[dir_id].first][temp_y - direction[dir_id].second] == color) {
            temp_x -= direction[dir_id].first;
            temp_y -= direction[dir_id].second;
            cnt_continuum++;
        }

        if (chess_board.IsVacant(temp_x - direction[dir_id].first, temp_y - direction[dir_id].second)) {
            cnt[1][0] = cnt_continuum;
            int cnt_s = cnt_continuum + 1;

            temp_x -= direction[dir_id].first;
            temp_y -= direction[dir_id].second;

            while (chess_board.IsInBoard(temp_x - direction[dir_id].first, temp_y - direction[dir_id].second) && chess_board.chesses_[temp_x - direction[dir_id].first][temp_y - direction[dir_id].second] == color) {
                temp_x -= direction[dir_id].first;
                temp_y -= direction[dir_id].second;
                cnt_s++;
            }
            if (chess_board.IsVacant(temp_x - direction[dir_id].first, temp_y - direction[dir_id].second))
                cnt_suppose[1][0] = cnt_s;
            else {
                cnt_suppose[1][1] = cnt_s;
                is_block[1][1] = true;
            }

        } else {
            cnt[1][1] = cnt_continuum;
            is_block[1][0] = true;
            is_block[1][1] = true;
        }

        // �жϻ���
        if (!is_block[0][1] && !is_block[1][0] && cnt_suppose[0][0] + cnt[1][0] >= 4) {
            if (++info.num_of_three >= 2) return info;
        } else if (!is_block[1][1] && !is_block[0][0] && cnt_suppose[1][0] + cnt[0][0] >= 4) {
            if (++info.num_of_three >= 2) return info;
        }

        if (!is_block[0][1] && !is_block[1][1] && cnt_suppose[0][0] - cnt[0][0] > 1 && cnt_suppose[1][0] - cnt[1][0] > 1) {
            if (cnt_suppose[0][0] + cnt[1][0] >= 4 && cnt_suppose[1][0] + cnt[0][0] >= 4) {
                if (++info.num_of_three >= 2) return info;
            }
        }

        // �жϻ��ĳ���
        // ��֤���������ִ��ڵ��ڱ���
        cnt[0][0] = std::max(cnt[0][0], cnt[0][1]);
        cnt[1][0] = std::max(cnt[1][0], cnt[1][1]);
        cnt_suppose[0][0] = std::max(cnt_suppose[0][0], cnt_suppose[0][1]);
        cnt_suppose[1][0] = std::max(cnt_suppose[1][0], cnt_suppose[0][1]);

        if ((!is_block[0][1] || !is_block[1][0]) && cnt_suppose[0][0] + cnt[1][0] >= 5) { // ǰsuppose ��suppose
            if (++info.num_of_four >= 2) return info;
        } else if ((!is_block[1][1] || !is_block[0][0]) && cnt_suppose[1][0] + cnt[0][0] >= 5) { // ��suppose ǰ��suppose
            if (++info.num_of_four >= 2) return info;
        }

        if (!is_block[0][0] && !is_block[1][0] && cnt_suppose[0][0] - cnt[0][0] > 1 && cnt_suppose[1][0] - cnt[1][0] > 1) {
            if (cnt_suppose[0][0] + cnt[1][0] >= 5 && cnt_suppose[1][0] + cnt[0][0] >= 5) {
                if (++info.num_of_four >= 2) return info;
            } else if (cnt_suppose[0][1] + cnt[1][1] >= 5 && cnt_suppose[1][0] + cnt[0][0] >= 5) {
                if (++info.num_of_four >= 2) return info;
            }
        }

        // �жϳ���
        if (cnt[1][1] + cnt[0][1] > 5) {
            info.num_of_length++;
            return info;
        }
    }
    return info;
}

bool Judge::IsGameWin(ChessBoard chess_board) {
    PII last_update = chess_board.LastUpdate();
    char color_of_chess = chess_board.cur_color_;
    for (int dir_id = 0; dir_id < 4; dir_id++) {
        int cnt_continuum = 1;
        int temp_x = last_update.first, temp_y = last_update.second;
        while (chess_board.IsInBoard(temp_x + direction[dir_id].first, temp_y + direction[dir_id].second) && chess_board.chesses_[temp_x + direction[dir_id].first][temp_y + direction[dir_id].second] == color_of_chess) {
            temp_x += direction[dir_id].first;
            temp_y += direction[dir_id].second;
            cnt_continuum++;
        }
        temp_x = last_update.first, temp_y = last_update.second;
        while (chess_board.IsInBoard(temp_x - direction[dir_id].first, temp_y - direction[dir_id].second) && chess_board.chesses_[temp_x - direction[dir_id].first][temp_y - direction[dir_id].second] == color_of_chess) {
            temp_x -= direction[dir_id].first;
            temp_y -= direction[dir_id].second;
            cnt_continuum++;
        }
        if (cnt_continuum == 5 && color_of_chess == 1) return true;
        if (cnt_continuum >= 5 && color_of_chess == 2) return true;
    }
    return false;
}

bool Judge::IsGameWinNoChess(ChessBoard chess_board, PII last_update, char color_of_chess) {
    for (int dir_id = 0; dir_id < 4; dir_id++) {
        int cnt_continuum = 1;
        int temp_x = last_update.first, temp_y = last_update.second;
        while (chess_board.IsInBoard(temp_x + direction[dir_id].first, temp_y + direction[dir_id].second) && chess_board.chesses_[temp_x + direction[dir_id].first][temp_y + direction[dir_id].second] == color_of_chess) {
            temp_x += direction[dir_id].first;
            temp_y += direction[dir_id].second;
            cnt_continuum++;
        }
        temp_x = last_update.first, temp_y = last_update.second;
        while (chess_board.IsInBoard(temp_x - direction[dir_id].first, temp_y - direction[dir_id].second) && chess_board.chesses_[temp_x - direction[dir_id].first][temp_y - direction[dir_id].second] == color_of_chess) {
            temp_x -= direction[dir_id].first;
            temp_y -= direction[dir_id].second;
            cnt_continuum++;
        }
        if (cnt_continuum == 5) return true;
    }
    return false;
}

bool Judge::IsForbiddenHand(ChessBoard chess_board) {
    PII last_update = chess_board.LastUpdate();
    if (last_update.first < 0 || last_update.first >= 15 || last_update.second < 0 || last_update.second >= 15) {
        std::cout << last_update.first << ' ' << last_update.second << std::endl;
        printf("out of range");
        return true;
    }
    if (IsGameWin(chess_board)) return false;
    chess_board.chesses_[last_update.first][last_update.second] = chess_board.cur_color_;

    // ����Ǻ��壬�ܽ�������
    if (chess_board.cur_color_) {
        PointInfo info = GetPointInfo(chess_board);

        if (info.num_of_three >= 2 || info.num_of_four >= 2 || info.num_of_length > 0) {
            return true;
        }
    }
    return false;
}
