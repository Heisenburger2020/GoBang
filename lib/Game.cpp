#include "Game.h"

using std::cin;
using std::cout;
using std::endl;

Game::Game() {
}

void Game::InitGame() {
    num_round_ = 0;
    chess_board_.InitChessBoard();
    // 画棋盘
    chess_board_.DrawChessBoard();
    // 选择模式
    SelectMode();
}

void Game::EndGame() {
    delete black_;
    delete white_;
}

void Game::SelectMode() {
    cout << "请选择游戏模式:" << endl;
    cout << "模式 1: 人人对战" << endl;
    cout << "模式 2: 人机对战" << endl;
    cout << "您的选择(输入 1 或者 2): ";
    cin >> game_mode_;

    while (game_mode_ != 1 && game_mode_ != 2) {
        cout << "您的输入有误.\n请重新选择游戏模式(输入 1 或者 2 ):";
        cin.clear();
        cin.sync();
        cin >> game_mode_;
    }

    if (game_mode_ == 2) {
        cout << "\n您的选择是人机对战。\n"
             << endl;
        SelectFirstHand();
    } else if (game_mode_ == 1) {
        cout << "\n您的选择是人人对战。\n"
             << endl;
        system("cls");
        black_ = new Human();
        black_->color_ = 1;
        black_->player_name_ = "黑棋玩家";
        black_->chess_shape_ = " (●) ";
        white_ = new Human();
        white_->color_ = 2;
        white_->player_name_ = "白棋玩家";
        white_->chess_shape_ = " (○) ";
    }
}

void Game::SelectFirstHand() {
    int mode;
    cout << "请选择是否先手" << endl;
    cout << "模式 1：先手黑棋" << endl;
    cout << "模式 2：后手白棋" << endl;
    cout << "您的选择是：";
    cin >> mode;
    cout << endl;

    while (mode != 1 && mode != 2) {
        cout << "您的输入有误.\n请重新选择是否先手(输入 1 或者 2):";
        cin.clear(); //清除流标记
        cin.sync();  //清空流
        cin >> mode;
    }

    if (mode == 1) {
        is_player_black_ = true;
        black_ = new Human();
        black_->color_ = 1;
        black_->player_name_ = "黑棋玩家";
        black_->chess_shape_ = " (●) ";
        white_ = new Machine();
        white_->color_ = 2;
        white_->player_name_ = "白棋电脑";
        white_->chess_shape_ = " (○) ";
    } else if (mode == 2) {
        is_player_black_ = false;
        black_ = new Machine();
        black_->color_ = 1;
        black_->player_name_ = "黑棋电脑";
        black_->chess_shape_ = " (●) ";
        white_ = new Human();
        white_->color_ = 2;
        white_->player_name_ = "白棋玩家";
        white_->chess_shape_ = " (○) ";
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
    std::cout << "\n是否再玩一局？【1】是  【2】否.\n 您的选择是(输入 1 或者 2 ):";

    std::cin >> is_regame;
    while (is_regame != 1 && is_regame != 2) {
        std::cout << "您的输入有误.\n是否再战一局？【1】是  【2】否.\n 您的选择是(输入 1 或者 2 ):";
        std::cin.clear();
        std::cin.sync();
        std::cin >> is_regame;
    }
    if (is_regame == 1) {
        // 如果再玩一局
        num_round_ = 0;

        if (game_mode_ == 2) {
            if (is_player_black_) {
                black_->player_name_ = "黑棋电脑";
                white_->player_name_ = "白棋玩家";
            } else {
                black_->player_name_ = "黑棋玩家";
                white_->player_name_ = "白棋电脑";
            }
            is_player_black_ = 1 - is_player_black_;
        }

        //重置棋盘
        chess_board_.InitChessBoard();

        system("cls");

        this->InitGame();
        this->StartGame();

        ////再次开始对战
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
        cout << "游戏结束！" << std::endl;
    }
}

void Game::GameOver(char color) {
    if (game_mode_ == 1) {
        // 玩家对战
        if (color == 1)
            cout << "黑棋玩家获胜！" << endl;
        else
            cout << "白棋玩家获胜" << endl;
    } else {
        // 人机对战
        if (is_player_black_ == 2 - color) {
            cout << "玩家获胜！" << endl;
        } else {
            cout << "电脑玩家获胜！" << endl;
        }
    }
}

void Game::HumanHumanMatch() {
    clock_t start_time, end_time;
    while (true) {
        // 下棋
        start_time = clock();
        black_->PlayChess(chess_board_, num_round_);
        end_time = clock();
        if (end_time - start_time > 15000) {
            cout << "黑棋超过15秒未下子" << endl;
            GameOver(2);
            break;
        }
        // 判断是否胜利
        if (Judge::IsGameWin(chess_board_)) {
            system("cls");
            chess_board_.DrawChessBoard();
            cout << "黑棋五子相连" << endl;
            GameOver(1);
            break;
        }

        // 判断禁手
        if (Judge::IsForbiddenHand(chess_board_)) {
            cout << "黑棋禁手！" << endl;
            GameOver(2);
            break;
        }

        if (num_round_ == 112) {
            cout << "平局！" << endl;
            break;
        }

        // 下棋
        start_time = clock();
        white_->PlayChess(chess_board_, num_round_);
        end_time = clock();
        if (end_time - start_time > 15000) {
            cout << "白棋超过15秒未下子" << endl;
            GameOver(1);
            break;
        }

        // 判断是否胜利
        if (Judge::IsGameWin(chess_board_)) {
            system("cls");
            chess_board_.DrawChessBoard();
            cout << "白棋五子相连" << endl;
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
        // 下棋
        start_time = clock();
        black_->PlayChess(chess_board_, num_round_);
        end_time = clock();
        if (end_time - start_time > 15000) {
            cout << "黑棋超过15秒未下子" << endl;
            GameOver(2);
            break;
        }

        // 判断是否胜利
        if (Judge::IsGameWin(chess_board_)) {
            system("cls");
            chess_board_.DrawChessBoard();
            cout << "黑棋五子相连" << endl;
            GameOver(1);
            break;
        }

        // 判断禁手
        if (Judge::IsForbiddenHand(chess_board_)) {
            cout << "黑棋禁手！" << endl;
            GameOver(2);
            break;
        }

        // 下棋
        start_time = clock();
        white_->PlayChess(chess_board_, num_round_);
        end_time = clock();
        if (end_time - start_time > 15000) {
            cout << "白棋超过15秒未下子" << endl;
            GameOver(1);
            break;
        }

        // 判断是否胜利
        if (Judge::IsGameWin(chess_board_)) {
            system("cls");
            chess_board_.DrawChessBoard();
            cout << "白棋五子相连" << endl;
            GameOver(2);
            break;
        }
        ++num_round_;
    }
    ReGame();
}