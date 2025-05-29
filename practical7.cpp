#include <iostream>
#include <vector>

using namespace std;

// Magic square mapping 
const int magicSquare[9] = {8, 1, 6, 3, 5, 7, 4, 9, 2};

int board[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2};  // empty slot = 2
int player = 3, computer = 5;  // X = 3 , O = 5

// Display Board
void displayBoard() {
    cout << "-------------" << endl;
    for (int i = 0; i < 9; i += 3) {
        cout << "| " << (board[i] == 2 ? ' ' : (board[i] == 3 ? 'X' : 'O')) << " | "
             << (board[i + 1] == 2 ? ' ' : (board[i + 1] == 3 ? 'X' : 'O')) << " | "
             << (board[i + 2] == 2 ? ' ' : (board[i + 2] == 3 ? 'X' : 'O')) << " |" << endl;
        cout << "-------------" << endl;
    }
}

// Check if player won by summing up the magic square values
bool checkWin(int mark) {
    int total = 0;
    vector<vector<int>> winConditions = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8},
                                         {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
                                         {0, 4, 8}, {2, 4, 6}};

    for (auto condition : winConditions) {
        total = 0;
        for (int pos : condition) {
            if (board[pos] == mark) {
                total += magicSquare[pos];  // Sum magic square values
            }
        }
        if (total == 15) {  
            return true;
        }
    }
    return false;
}

// Check for tie 
bool checkTie() {
    for (int slot : board) {
        if (slot == 2) {
            return false; 
        }
    }
    return true;
}

// Make a move
void makeMove(int pos, int mark) {
    board[pos - 1] = mark; 
}

// Check if a move can result in a win for the current player
int posswin(int mark) {
    for (int i = 0; i < 9; i++) {
        if (board[i] == 2) {  // Check available slot
            board[i] = mark;  // Simulate the move
            if (checkWin(mark)) {  // If it results in a win
                board[i] = 2;  // Undo the move
                return i + 1;  // Return the position (1-based index)
            }
            board[i] = 2;  // Undo the move
        }
    }
    return 0;  // No winning move found
}

// Computer decides its move
int computerMove() {
    // Check if the computer can win
    int move = posswin(computer);
    if (move) return move;

    // Check if the player is about to win and block them
    move = posswin(player);
    if (move) return move;

    // Prioritize center
    if (board[4] == 2) {
        return 5;
    }

    // Prioritize the corners
    vector<int> corners = {1, 3, 7, 9};
    for (int corner : corners) {
        if (board[corner - 1] == 2) {
            return corner;
        }
    }

    // Otherwise, pick any available spot
    for (int i = 1; i <= 9; i++) {
        if (board[i - 1] == 2) {
            return i;
        }
    }

    return 0; 
}

// Main Game Loop
void playGame() {
    int pos;
    displayBoard();

    while (true) {
        // Player's move
        cout << "Player, choose your slot (1-9): ";
        cin >> pos;

        if (pos < 1 || pos > 9 || board[pos - 1] != 2) {
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
