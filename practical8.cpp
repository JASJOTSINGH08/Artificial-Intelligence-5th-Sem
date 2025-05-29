#include <iostream>
#include <limits.h>
using namespace std;

char board[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

// Function to print the board
void printBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// Function to check if there are moves left
bool isMovesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return true;
    return false;
}

// Function to evaluate the board
int evaluate() {
    // Checking Rows for X or O victory
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == 'X')
                return +10;
            else if (board[row][0] == 'O')
                return -10;
        }
    }
    // Checking Columns for X or O victory
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == 'X')
                return +10;
            else if (board[0][col] == 'O')
                return -10;
        }
    }
    // Checking Diagonals for X or O victory
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == 'X')
            return +10;
        else if (board[0][0] == 'O')
            return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == 'X')
            return +10;
        else if (board[0][2] == 'O')
            return -10;
    }

    return 0; // If no one has won
}

// Minimax algorithm to find the best move
int minimax(int depth, bool isMax) {
    int score = evaluate();

    // If Maximizer has won
    if (score == 10)
        return score;

    // If Minimizer has won
    if (score == -10)
        return score;

    // If no moves left, it's a draw
    if (!isMovesLeft())
        return 0;

    // Maximizer's move
    if (isMax) {
        int best = -1000;

        // Traverse all cells
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Check if cell is empty
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j];
                    board[i][j] = 'X'; // Make the move

                    best = max(best, minimax(depth + 1, !isMax));

                    board[i][j] = temp; // Undo the move
                }
            }
        }
        return best;
    }
    // Minimizer's move
    else {
        int best = 1000;

        // Traverse all cells
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Check if cell is empty
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j];
                    board[i][j] = 'O'; // Make the move

                    best = min(best, minimax(depth + 1, !isMax));

                    board[i][j] = temp; // Undo the move
                }
            }
        }
        return best;
    }
}

// Find the best possible move for the AI
pair<int, int> findBestMove() {
    int bestVal = -1000;
    pair<int, int> bestMove = {-1, -1};

    // Traverse all cells
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Check if cell is empty
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char temp = board[i][j];
                board[i][j] = 'X'; // AI's move

                int moveVal = minimax(0, false);

                board[i][j] = temp; // Undo the move

                // If the value of the current move is more than the best value, update the best move
                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

// Check if there is a winner
bool checkWinner(char player) {
    int score = evaluate();
    if (score == 10 && player == 'X') {
        cout << "AI wins!\n";
        return true;
    } else if (score == -10 && player == 'O') {
        cout << "You win!\n";
        return true;
    } else if (!isMovesLeft()) {
        cout << "It's a draw!\n";
        return true;
    }
    return false;
}

int main() {
    printBoard();
    while (true) {
        // User makes a move
        int userMove;
        cout << "Enter your move (1-9): ";
        cin >> userMove;

        userMove--; // Adjust index to 0-based
        int row = userMove / 3;
        int col = userMove % 3;

        if (board[row][col] != 'X' && board[row][col] != 'O') {
            board[row][col] = 'O'; // Player is 'O'
        } else {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        printBoard();

        // Check if the user has won
        if (checkWinner('O')) break;

        // AI makes its move
        pair<int, int> bestMove = findBestMove();
        board[bestMove.first][bestMove.second] = 'X'; // AI is 'X'

        printBoard();

        // Check if the AI has won
        if (checkWinner('X')) break;
    }

    return 0;
}
