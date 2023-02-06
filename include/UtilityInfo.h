#pragma once

#include "PseudoHeap.h"

class UtilityInfo {
public:

    UtilityInfo();

    int score_;
    int cur_id_;
    PointScore pts_[4];

    void CountScore(PseudoHeap self, PseudoHeap oppo);
};
