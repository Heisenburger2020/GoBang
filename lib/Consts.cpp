#include "Consts.h"

PII Consts::direction[8] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };

int Consts::live_one_ = 50;
int Consts::live_two_ = live_one_ * 3;
int Consts::live_three_ = live_two_ * 3;
int Consts::live_four_ = live_three_ * 5;
int Consts::five_ = live_four_ * 10;
int Consts::live_[6] = {0, live_one_, live_two_, live_three_, live_four_, five_};

int Consts::blocked_one_ = live_one_ / 3;
int Consts::blocked_two_ = live_two_ / 3;
int Consts::blocked_three_ = live_three_ / 3;
int Consts::blocked_four_ = live_four_ / 3;
int Consts::blocked_[6] = {0, blocked_one_, blocked_two_, blocked_three_, blocked_four_, five_};

int Consts::blocked_one_diff_ = live_one_ / 3 * 2;
int Consts::blocked_two_diff_ = live_two_ / 3 * 2;
int Consts::blocked_three_diff_ = live_three_ / 3 * 2;
int Consts::blocked_four_diff_ = live_four_ / 3 * 2;
int Consts::blocked_diff_[6] = {0, blocked_one_diff_, blocked_two_diff_, blocked_three_diff_, blocked_four_diff_, 0};


