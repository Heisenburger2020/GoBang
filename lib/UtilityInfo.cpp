#include "UtilityInfo.h"

UtilityInfo::UtilityInfo() {
    score_ = -1;
    cur_id_ = -1;
}

void UtilityInfo::CountScore(PseudoHeap self, PseudoHeap oppo) {
    int res = 0;
    if (self.four_highest_[0].x_ == oppo.four_highest_[0].x_ && self.four_highest_[0].y_ == oppo.four_highest_[0].y_) {
        for (int i = 0; i < 2; i++) {
            if (self.cur_idx_ >= i) res += self.four_highest_[i].score_;
            if (oppo.cur_idx_ >= i) res -= oppo.four_highest_[i + 1].score_;
        }
    } else {
        for (int i = 0; i < 3; i++) {
            if (self.cur_idx_ >= i) res += self.four_highest_[i].score_;
            if (oppo.cur_idx_ >= i) res -= oppo.four_highest_[i].score_;
        }
    }
    score_ = res;
}