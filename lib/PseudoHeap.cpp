#include "PseudoHeap.h"

PseudoHeap::PseudoHeap() {
    cur_idx_ = -1;
    for (int i = 0; i < 4; i++) {
        four_highest_[i].x_ = -1;
        four_highest_[i].y_ = -1;
        four_highest_[i].score_ = -0x3f3f3f3f;
    }
};

void PseudoHeap::AddScore(int s, int x, int y) {
    if (cur_idx_ == -1) {
        four_highest_[++cur_idx_] = {s, x, y};
    } else {
        if (s > four_highest_[cur_idx_].score_) {
            if (cur_idx_ < 3) {
                four_highest_[++cur_idx_] = {s, x, y};
            } else {
                four_highest_[3] = {s, x, y};
                std::sort(four_highest_, four_highest_ + 4, PointScore::cmp);
            }
        }
    }
}