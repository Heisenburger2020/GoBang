#pragma once

#include <utility>
#include <cstdio>
#include <algorithm>

#include "Consts.h"
#include "UtilityInfo.h"
#include "PseudoHeap.h"

#define ROW 15
#define COLUMN 15
#define INIT_SCORE 1
#define CONVO_SCORE 50
#define UTILITY_ALPHA 1.3 // ��������ָ��
#define UTILITY_BETA 0.8 // �з�����ָ��

typedef std::pair<int, int> PII;
typedef std::pair<char, char> PCC;
typedef int (*TwoDimArray)[COLUMN];

class Judge;

class ChessBoard
{
public:
	char chesses_[ROW][COLUMN]; // ��¼����λ��
	PCC pos_last_black_;
	PCC pos_last_white_;
	char cur_color_;
	int black_socre_[ROW][COLUMN]; // �������ط��º��ӣ������ж�����
	int white_socre_[ROW][COLUMN]; // �������ط��°��ӣ������ж�����
	static int init_score_[ROW][COLUMN];

	ChessBoard();
    ChessBoard(ChessBoard*);
    void InitScore();
    void InitChessBoard();
	void DrawChessBoard();
	void DrawChess(int x, int y, int col = 0);
	void AddChess(int x, int y, char color, bool is_HumanMachine = true);
	void UtilityAssess(int x, int y);
    UtilityInfo EvaluateBoardUtility(char color);

	TwoDimArray ScoreSameColor(char color);
    TwoDimArray ScoreDiffColor(char color);
    bool IsVacant(int x, int y);
    bool IsInBoard(int x, int y);
    PII LastUpdate();
};

