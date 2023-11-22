#include <iostream>
#include <vector>

using namespace std;

void initializeBoard(vector<vector<char>>& board);
void displayBoard(const vector<vector<char>>& board);
bool makeMove(vector<vector<char>>& board, char currentPlayer, int row, int col);
bool checkWin(const vector<vector<char>>& board, char currentPlayer);
bool checkDraw(const vector<vector<char>>& board);
void switchPlayer(char& currentPlayer);
bool playAgain();

int main() {
    do {
        vector<vector<char>> board(3, vector<char>(3, ' '));
        char currentPlayer = 'X';
        bool gameWon = false;

        initializeBoard(board);

        do {
            displayBoard(board);

            int row, col;
            cout << "Player " << currentPlayer << ", enter your move (row and column): ";
            cin >> row >> col;

            if (makeMove(board, currentPlayer, row, col)) {
                gameWon = checkWin(board, currentPlayer);
                if (!gameWon) {
                    if (checkDraw(board)) {
                        displayBoard(board);
                        cout << "It's a draw!" << endl;
                        break;
                    }
                }
                switchPlayer(currentPlayer);
            } else {
                cout << "Invalid move. Try again." << endl;
            }

        } while (!gameWon);

    } while (playAgain());

    cout << "Thanks for playing Tic-Tac-Toe!" << endl;

    return 0;
}

void initializeBoard(vector<vector<char>>& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = ' ';
        }
    }
}

void displayBoard(const vector<vector<char>>& board) {
    cout << " 0 1 2" << endl;
    for (int i = 0; i < 3; ++i) {
        cout << i << " ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool makeMove(vector<vector<char>>& board, char currentPlayer, int row, int col) {
    if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
        return false;
    }
    board[row][col] = currentPlayer;
    return true;
}

bool checkWin(const vector<vector<char>>& board, char currentPlayer) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) {
            cout << "Player " << currentPlayer << " wins!" << endl;
            return true;
        }
        if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer) {
            cout << "Player " << currentPlayer << " wins!" << endl;
            return true;
        }
    }

    if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) {
        cout << "Player " << currentPlayer << " wins!" << endl;
        return true;
    }

    if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer) {
        cout << "Player " << currentPlayer << " wins!" << endl;
        return true;
    }

    return false;
}

bool checkDraw(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

void switchPlayer(char& currentPlayer) {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

bool playAgain() {
    char choice;
    cout << "Do you want to play again? (y/n): ";
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}
