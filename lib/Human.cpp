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
	cout << "\n�ִ�" << num_round << ": ";
	cout << player_name_ << chess_shape_ << "��������������(��:A1 �� a1):";
	cin >> column >> row;
    
	while (cin.fail()) {
		system("cls");
		chess_board.DrawChessBoard();
		cin.clear();
		cin.sync();
		cout << "\n����Ƿ�.\n�����������������꣺";
		cin >> column >> row;
	}
	// ��һ���ӱ�����Ԫ
	if (num_round == 0 && color_ == 1) {
		while ((column != 'H' && row != 8) || (column != 'h' && row != 8)) {
			system("cls");
			chess_board.DrawChessBoard();
			cout << "\n��һ�����ӱ���������Ԫ��H8.\n�����������������꣺";
			cin >> column >> row;
		}
	}

	// �ж��Ƿ�Ϸ�
	while ((!(column >= 'a' && column <= 'o') && !(column >= 'A' && column <= 'O')) || row > 15 || row < 1) {
		system("cls");
		chess_board.DrawChessBoard();
		cout << "\n����Ƿ�.\n�����������������꣺";
		cin >> column >> row;
		while (cin.fail()) {
			system("cls");
			chess_board.DrawChessBoard();
			cin.clear();
			cin.sync();
			cout << "\n����Ƿ�.\n�����������������꣺";
			cin >> column >> row;
		}
	}
	// �ж��µ�λ���Ƿ���������
	int x, y;
	while (true) {
		x = row_char2int(row);
		y = col_int2int(column);

		if (chess_board.chesses_[x][y]) {
			// ������
			system("cls");
			chess_board.DrawChessBoard();
			cout << "\n��������괦�������ӡ�\n�����������������꣺";
			cin >> column >> row;
			while (cin.fail()) {
				system("cls");
				chess_board.DrawChessBoard();
				cin.clear();
				cin.sync();
				cout << "\n����Ƿ�.\n�����������������꣺";
				cin >> column >> row;
			}
		}
		else {
			// û������
			break;
		}
			
	}

	chess_board.AddChess(x, y, color_, true);
}
