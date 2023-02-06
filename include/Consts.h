#pragma once

#include <utility>

typedef std::pair<int, int> PII;

class Consts
{
public:
	static PII direction[8];


	static int live_one_;
	static int live_two_;
	static int live_three_;
	static int live_four_;
    static int live_[6];

	static int blocked_one_;
	static int blocked_two_;
	static int blocked_three_;
	static int blocked_four_;
    static int blocked_[6];

    static int blocked_one_diff_;
    static int blocked_two_diff_;
    static int blocked_three_diff_;
    static int blocked_four_diff_;
    static int blocked_diff_[6];

	static int five_;
};

