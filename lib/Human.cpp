#include "Human.h"


#include <iostream>
#include <cstdio>

using std::cout;
using std::cin;
using std::endl;

Human::Human() {

}

int Human::col_int2int(char id) {
	if (id >= 'A' && id <= 'O') return id - 'A';
	else if (id >= 'a' && id <= 'o') return id - 'a';
	return -1;
}

int Human::row_char2int(int id) {
	if (id >= 1 && id <= 15) return 15 - id;
	return -1;
}

void Human::PlayChess(ChessBoard &chess_board, int num_round) {
	int row;
	char column;
	system("cls");
	chess_board.DrawChessBoard();
	cout << "\n轮次" << num_round << ": ";
	cout << player_name_ << chess_shape_ << "请输入棋子坐标(如:A1 或 a1):";
	cin >> column >> row;
    
	while (cin.fail()) {
		system("cls");
		chess_board.DrawChessBoard();
		cin.clear();
		cin.sync();
		cout << "\n输入非法.\n请重新输入棋子坐标：";
		cin >> column >> row;
	}
	// 第一个子必须天元
	if (num_round == 0 && color_ == 1) {
		while ((column != 'H' && row != 8) || (column != 'h' && row != 8)) {
			system("cls");
			chess_board.DrawChessBoard();
			cout << "\n第一颗棋子必须落在天元：H8.\n请重新输入棋子坐标：";
			cin >> column >> row;
		}
	}

	// 判断是否合法
	while ((!(column >= 'a' && column <= 'o') && !(column >= 'A' && column <= 'O')) || row > 15 || row < 1) {
		system("cls");
		chess_board.DrawChessBoard();
		cout << "\n输入非法.\n请重新输入棋子坐标：";
		cin >> column >> row;
		while (cin.fail()) {
			system("cls");
			chess_board.DrawChessBoard();
			cin.clear();
			cin.sync();
			cout << "\n输入非法.\n请重新输入棋子坐标：";
			cin >> column >> row;
		}
	}
	// 判断下的位置是否能有棋子
	int x, y;
	while (true) {
		x = row_char2int(row);
		y = col_int2int(column);

		if (chess_board.chesses_[x][y]) {
			// 有棋子
			system("cls");
			chess_board.DrawChessBoard();
			cout << "\n输入的坐标处已有棋子。\n请重新输入棋子坐标：";
			cin >> column >> row;
			while (cin.fail()) {
				system("cls");
				chess_board.DrawChessBoard();
				cin.clear();
				cin.sync();
				cout << "\n输入非法.\n请重新输入棋子坐标：";
				cin >> column >> row;
			}
		}
		else {
			// 没有棋子
			break;
		}
			
	}

	chess_board.AddChess(x, y, color_, true);
}
