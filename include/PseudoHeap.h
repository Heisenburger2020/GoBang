#pragma once

#include <cstring>
#include <algorithm>

struct PointScore {
    int score_ = -1;
    int x_ = -1;
    int y_ = -1;

    static bool cmp(PointScore a, PointScore b) {
        return a.score_ > b.score_;
    }
};

class PseudoHeap {
public:
    int cur_idx_;
    PointScore four_highest_[4];

    PseudoHeap();
    void AddScore(int s, int x, int y);
};
