#include <iostream>
#include <vector>

using namespace std;

char board[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char player = 'X', computer = 'O' ;

// Display Board
void displayBoard() {
    cout << "-------------" << endl;
    for (int i = 0; i < 9; i += 3) {
        cout << "| " << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << " |" << endl;
        cout << "-------------" << endl;
    }
}

// Win condition
bool checkWin(char mark) {
    vector<vector<int>> winConditions = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, 
                                         {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
                                         {0, 4, 8}, {2, 4, 6}};
    
    for (auto condition : winConditions) {
        if (board[condition[0]] == mark && board[condition[1]] == mark && board[condition[2]] == mark)
            return true;
    }
    return false;
}

// Check for tie
bool checkTie() {
    for (char slot : board) {
        if (slot != 'X' && slot != 'O') {
            return false;
        }
    }
    return true;
}

// Make move
void makeMove(int pos, char mark) {
    board[pos - 1] = mark;
}

// Prioritize moves (center, corners)
int computerMove() {
    // Check if computer can win
    for (int i = 1; i <= 9; i++) {
        if (board[i-1] != 'X' && board[i-1] != 'O') {
            char temp = board[i-1];
            board[i-1] = computer;
            if (checkWin(computer)) {
                return i;
            } 
            board[i-1] = temp;
        }
    }

    // Check if player is about to win 
    for (int i = 1; i <= 9; i++) {
        if (board[i-1] != 'X' && board[i-1] != 'O') {
            char temp = board[i-1];
            board[i-1] = player;
            if (checkWin(player)) {
                board[i-1] = temp;
                return i;
            }
            board[i-1] = temp;
        }
    }

    // Prioritize center
    if (board[4] != 'X' && board[4] != 'O') {
        return 5;
    }

    // Prioritize the corners
    vector<int> corners = {1, 3, 7, 9};
    for (int corner : corners) {
        if (board[corner - 1] != 'X' && board[corner - 1] != 'O') {
            return corner;
        }
    }

    // Otherwise, pick another better spot
    for (int i = 1; i <= 9; i++) {
        if (board[i-1] != 'X' && board[i-1] != 'O') {
            return i;
        }
    }

    return 0; 
}

// Main Game
void playGame() {
    int pos;
    displayBoard();

    while (true) {
        // Player's move
        cout << "Player, choose your slot: ";
        cin >> pos;

        if (pos < 1 || pos > 9 || board[pos - 1] == 'X' || board[pos - 1] == 'O') {
            cout << "Invalid move, try again." << endl;
            continue;
        }
        makeMove(pos, player);
        displayBoard();

        // Check if player wins
        if (checkWin(player)) {
            cout << "Player wins!" << endl;
            break;
        }

        // Check if the game is a tie
        if (checkTie()) {
            cout << "It's a tie!" << endl;
            break;
        }

        // Computer's Move
        int compMove = computerMove();
        cout << "Computer chose slot: " << compMove << endl;
        makeMove(compMove, computer);
        displayBoard();

        // Check if Computer Wins
        if (checkWin(computer)) {
            cout << "Computer wins!" << endl;
            break;
        }

        // Check if game is a tie after computer's move
        if (checkTie()) {
            cout << "It's a tie!" << endl;
            break;
        }
    }
}

int main() {
    playGame();
    return 0;
}
