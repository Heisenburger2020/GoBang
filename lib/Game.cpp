#include "Game.h"

using std::cin;
using std::cout;
using std::endl;

Game::Game() {
}

void Game::InitGame() {
    num_round_ = 0;
    chess_board_.InitChessBoard();
    // ������
    chess_board_.DrawChessBoard();
    // ѡ��ģʽ
    SelectMode();
}

void Game::EndGame() {
    delete black_;
    delete white_;
}

void Game::SelectMode() {
    cout << "��ѡ����Ϸģʽ:" << endl;
    cout << "ģʽ 1: ���˶�ս" << endl;
    cout << "ģʽ 2: �˻���ս" << endl;
    cout << "����ѡ��(���� 1 ���� 2): ";
    cin >> game_mode_;

    while (game_mode_ != 1 && game_mode_ != 2) {
        cout << "������������.\n������ѡ����Ϸģʽ(���� 1 ���� 2 ):";
        cin.clear();
        cin.sync();
        cin >> game_mode_;
    }

    if (game_mode_ == 2) {
        cout << "\n����ѡ�����˻���ս��\n"
             << endl;
        SelectFirstHand();
    } else if (game_mode_ == 1) {
        cout << "\n����ѡ�������˶�ս��\n"
             << endl;
        system("cls");
        black_ = new Human();
        black_->color_ = 1;
        black_->player_name_ = "�������";
        black_->chess_shape_ = " (��) ";
        white_ = new Human();
        white_->color_ = 2;
        white_->player_name_ = "�������";
        white_->chess_shape_ = " (��) ";
    }
}

void Game::SelectFirstHand() {
    int mode;
    cout << "��ѡ���Ƿ�����" << endl;
    cout << "ģʽ 1�����ֺ���" << endl;
    cout << "ģʽ 2�����ְ���" << endl;
    cout << "����ѡ���ǣ�";
    cin >> mode;
    cout << endl;

    while (mode != 1 && mode != 2) {
        cout << "������������.\n������ѡ���Ƿ�����(���� 1 ���� 2):";
        cin.clear(); //��������
        cin.sync();  //�����
        cin >> mode;
    }

    if (mode == 1) {
        is_player_black_ = true;
        black_ = new Human();
        black_->color_ = 1;
        black_->player_name_ = "�������";
        black_->chess_shape_ = " (��) ";
        white_ = new Machine();
        white_->color_ = 2;
        white_->player_name_ = "�������";
        white_->chess_shape_ = " (��) ";
    } else if (mode == 2) {
        is_player_black_ = false;
        black_ = new Machine();
        black_->color_ = 1;
        black_->player_name_ = "�������";
        black_->chess_shape_ = " (��) ";
        white_ = new Human();
        white_->color_ = 2;
        white_->player_name_ = "�������";
        white_->chess_shape_ = " (��) ";
    }
}

void Game::StartGame() {
    if (game_mode_ == 1) {
        HumanHumanMatch();
    } else {
        HumanMachineMatch();
    }
}

void Game::ReGame() {
    int is_regame;
    std::cout << "\n�Ƿ�����һ�֣���1����  ��2����.\n ����ѡ����(���� 1 ���� 2 ):";

    std::cin >> is_regame;
    while (is_regame != 1 && is_regame != 2) {
        std::cout << "������������.\n�Ƿ���սһ�֣���1����  ��2����.\n ����ѡ����(���� 1 ���� 2 ):";
        std::cin.clear();
        std::cin.sync();
        std::cin >> is_regame;
    }
    if (is_regame == 1) {
        // �������һ��
        num_round_ = 0;

        if (game_mode_ == 2) {
            if (is_player_black_) {
                black_->player_name_ = "�������";
                white_->player_name_ = "�������";
            } else {
                black_->player_name_ = "�������";
                white_->player_name_ = "�������";
            }
            is_player_black_ = 1 - is_player_black_;
        }

        //��������
        chess_board_.InitChessBoard();

        system("cls");

        this->InitGame();
        this->StartGame();

        ////�ٴο�ʼ��ս
        //if (game_mode_ == 1) {
        //    HumanHumanMatch();
        //} else {
        //    if (is_player_black_) {
        //        black_ = new Human();
        //        white_ = new Machine();
        //    } else {
        //        white_ = new Human();
        //        black_ = new Machine();
        //    }
        //    HumanMachineMatch();
        //}
    } else {
        cout << "��Ϸ������" << std::endl;
    }
}

void Game::GameOver(char color) {
    if (game_mode_ == 1) {
        // ��Ҷ�ս
        if (color == 1)
            cout << "������һ�ʤ��" << endl;
        else
            cout << "������һ�ʤ" << endl;
    } else {
        // �˻���ս
        if (is_player_black_ == 2 - color) {
            cout << "��һ�ʤ��" << endl;
        } else {
            cout << "������һ�ʤ��" << endl;
        }
    }
}

void Game::HumanHumanMatch() {
    clock_t start_time, end_time;
    while (true) {
        // ����
        start_time = clock();
        black_->PlayChess(chess_board_, num_round_);
        end_time = clock();
        if (end_time - start_time > 15000) {
            cout << "���峬��15��δ����" << endl;
            GameOver(2);
            break;
        }
        // �ж��Ƿ�ʤ��
        if (Judge::IsGameWin(chess_board_)) {
            system("cls");
            chess_board_.DrawChessBoard();
            cout << "������������" << endl;
            GameOver(1);
            break;
        }

        // �жϽ���
        if (Judge::IsForbiddenHand(chess_board_)) {
            cout << "������֣�" << endl;
            GameOver(2);
            break;
        }

        if (num_round_ == 112) {
            cout << "ƽ�֣�" << endl;
            break;
        }

        // ����
        start_time = clock();
        white_->PlayChess(chess_board_, num_round_);
        end_time = clock();
        if (end_time - start_time > 15000) {
            cout << "���峬��15��δ����" << endl;
            GameOver(1);
            break;
        }

        // �ж��Ƿ�ʤ��
        if (Judge::IsGameWin(chess_board_)) {
            system("cls");
            chess_board_.DrawChessBoard();
            cout << "������������" << endl;
            GameOver(2);
            break;
        }

        ++num_round_;
    }
    ReGame();
}

void Game::HumanMachineMatch() {
    //system("cls");
    clock_t start_time, end_time;
    while (true) {
        // ����
        start_time = clock();
        black_->PlayChess(chess_board_, num_round_);
        end_time = clock();
        if (end_time - start_time > 15000) {
            cout << "���峬��15��δ����" << endl;
            GameOver(2);
            break;
        }

        // �ж��Ƿ�ʤ��
        if (Judge::IsGameWin(chess_board_)) {
            system("cls");
            chess_board_.DrawChessBoard();
            cout << "������������" << endl;
            GameOver(1);
            break;
        }

        // �жϽ���
        if (Judge::IsForbiddenHand(chess_board_)) {
            cout << "������֣�" << endl;
            GameOver(2);
            break;
        }

        // ����
        start_time = clock();
        white_->PlayChess(chess_board_, num_round_);
        end_time = clock();
        if (end_time - start_time > 15000) {
            cout << "���峬��15��δ����" << endl;
            GameOver(1);
            break;
        }

        // �ж��Ƿ�ʤ��
        if (Judge::IsGameWin(chess_board_)) {
            system("cls");
            chess_board_.DrawChessBoard();
            cout << "������������" << endl;
            GameOver(2);
            break;
        }
        ++num_round_;
    }
    ReGame();
}