#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

char board[3][3];
string playerName;
int difficulty; // 1-Easy, 2-Medium, 3-Hard

//It will clear the board for next round
void resetBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

//It will display the board
void displayBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "---|---|---\n";
    }
}

// Check moves left
bool isMovesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return true;
    return false;
}

// Evaluate board
int evaluate() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2]) {
            if (board[i][0] == 'O') return 10;
            if (board[i][0] == 'X') return -10;
        }
    }

    for (int j = 0; j < 3; j++) {
        if (board[0][j] == board[1][j] &&
            board[1][j] == board[2][j]) {
            if (board[0][j] == 'O') return 10;
            if (board[0][j] == 'X') return -10;
        }
    }

    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
        if (board[0][0] == 'O') return 10;
        if (board[0][0] == 'X') return -10;
    }

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
        if (board[0][2] == 'O') return 10;
        if (board[0][2] == 'X') return -10;
    }

    return 0;
}

// Minimax (Hard AI)
int minimax(bool isMax) {
    int score = evaluate();
    if (score == 10 || score == -10) return score;
    if (!isMovesLeft()) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    best = max(best, minimax(false));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    best = min(best, minimax(true));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

// Random move (Easy AI)
void randomMove() {
    int i, j;
    do {
        i = rand() % 3;
        j = rand() % 3;
    } while (board[i][j] != ' ');
    board[i][j] = 'O';
}

// Best move (Hard AI)
void bestMove() {
    int bestVal = -1000, r = -1, c = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int moveVal = minimax(false);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    bestVal = moveVal;
                    r = i;
                    c = j;
                }
            }
        }
    }
    board[r][c] = 'O';
}

// AI move based on difficulty
void aiMove() {
    if (difficulty == 1)
        randomMove();
    else if (difficulty == 2)
        (rand() % 2 == 0) ? randomMove() : bestMove();
    else
        bestMove();
}

int main() {
    srand(time(0));
    char playAgain;

    do {
        resetBoard();
        cout << "\nEnter your name: ";
        cin >> playerName;

        cout << "\nChoose Difficulty:\n";
        cout << "1. Easy\n2. Medium\n3. Hard\n";
        cout << "Enter choice: ";
        cin >> difficulty;

        while (true) {
            displayBoard();
            int row, col;
            cout << playerName << ", enter row and column (0-2): ";
            cin >> row >> col;

            if (board[row][col] != ' ') {
                cout << "Invalid move. Try again.\n";
                continue;
            }

            board[row][col] = 'X';

            if (evaluate() == -10) {
                displayBoard();
                cout << playerName << " wins! 🎉\n";
                break;
            }

            if (!isMovesLeft()) {
                displayBoard();
                cout << "It's a draw.\n";
                break;
            }

            aiMove();

            if (evaluate() == 10) {
                displayBoard();
                cout << "AI wins. 🤖\n";
                break;
            }

            if (!isMovesLeft()) {
                displayBoard();
                cout << "It's a draw.\n";
                break;
            }
        }

        cout << "\nPlay again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    return 0;
}
