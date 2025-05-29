#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

int M, N, K, solutionCount = 0;
int rowMove[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
int colMove[] = { 1, -1, 1, -1, 2, -2, 2, -2 };

bool isSafe(const vector<vector<int>>& board, int row, int col) {
    for (int i = 0; i < 8; i++) {
        int newRow = row + rowMove[i];
        int newCol = col + colMove[i];
        if (newRow >= 0 && newRow < M && newCol >= 0 && newCol < N && board[newRow][newCol] == 1) {
            return false;
        }
    }
    return true;
}

bool findSolutions(vector<vector<int>>& board, int placedKnights, int row, int col, bool showFirst) {
    if (placedKnights == K) {
        solutionCount++;
        if (showFirst && solutionCount == 1) {
            cout << "Solution found:\n";
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    cout << (board[i][j] == 1 ? "K " : ". ");
                }
                cout << endl;
            }
            cout << endl;
        }
        return true;
    }

    for (int i = row; i < M; i++) {
        for (int j = (i == row ? col : 0); j < N; j++) {
            if (isSafe(board, i, j)) {
                board[i][j] = 1;
                findSolutions(board, placedKnights + 1, i, j + 1, showFirst);
                board[i][j] = 0;
            }
        }
    }
    return false;
}

int main() {
    cout << "Enter board dimensions (M x N): ";
    cin >> M >> N;
    cout << "Enter number of knights (K): ";
    cin >> K;

    vector<vector<int>> board(M, vector<int>(N, 0));

    auto startTime = chrono::high_resolution_clock::now();
    findSolutions(board, 0, 0, 0, true);  // Only display the first solution
    auto endTime = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsedTime = endTime - startTime;
    cout << "Time taken: " << elapsedTime.count() << " seconds\n";
    cout << "Number of solutions found: " << solutionCount << endl;

    return 0;
}
