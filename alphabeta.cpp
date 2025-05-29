#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<int> board(9, 2); 
int User = 3;        
int Computer = 5;      
int maxDepth = 4;      
int cntMinimax = 0;     
int cntAlphaBeta = 0;    

void displayBoard()
{
    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0)
            cout << endl;
        cout << (board[i] == User ? "X " : (board[i] == Computer ? "O " : "- "));
    }
    cout << endl;
}

bool isWin(const vector<int> &board, int player)
{
    for (int i = 0; i < 3; i++)
    {
        if ((board[i * 3] == player && board[i * 3 + 1] == player && board[i * 3 + 2] == player) ||
            (board[i] == player && board[i + 3] == player && board[i + 6] == player))
            return true;
    }
    return (board[0] == player && board[4] == player && board[8] == player) ||
           (board[2] == player && board[4] == player && board[6] == player);
}

bool isDraw(const vector<int> &board)
{
    for (int cell : board)
    {
        if (cell == 2)
            return false;
    }
    return true;
}

vector<int> availableMoves(const vector<int> &board)
{
    vector<int> moves;
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == 2)
            moves.push_back(i);
    }
    return moves;
}

int minimax(vector<int> &board, int depth, bool isMaximizing)
{
    cntMinimax++;

    if (isWin(board, Computer))
        return 10 - depth;
    if (isWin(board, User))
        return depth - 10;
    if (isDraw(board) || depth >= maxDepth) 
        return 0;

    int bestScore = isMaximizing ? INT_MIN : INT_MAX;
    vector<int> moves = availableMoves(board);

    for (int move : moves)
    {
        board[move] = isMaximizing ? Computer : User;
        int score = minimax(board, depth + 1, !isMaximizing);
        board[move] = 2; 
        bestScore = isMaximizing ? max(bestScore, score) : min(bestScore, score);
    }
    return bestScore;
}

int alphaBeta(vector<int> &board, int depth, int alpha, int beta, bool isMaximizing)
{
    cntAlphaBeta++;

    if (isWin(board, Computer))
        return 10 - depth;
    if (isWin(board, User))
        return depth - 10;
    if (isDraw(board) || depth >= maxDepth) 
        return 0;

    vector<int> moves = availableMoves(board);
    if (isMaximizing)
    {
        int bestScore = INT_MIN;
        for (int move : moves)
        {
            board[move] = Computer;
            int score = alphaBeta(board, depth + 1, alpha, beta, false);
            board[move] = 2; 
            bestScore = max(bestScore, score);
            alpha = max(alpha, bestScore);
            if (beta <= alpha)
                break; 
        }
        return bestScore;
    }
    else
    {
        int bestScore = INT_MAX;
        for (int move : moves)
        {
            board[move] = User;
            int score = alphaBeta(board, depth + 1, alpha, beta, true);
            board[move] = 2; 
            bestScore = min(bestScore, score);
            beta = min(beta, bestScore);
            if (beta <= alpha)
                break; 
        }
        return bestScore;
    }
}

int main()
{
    cntMinimax = 0;
    vector<int> tempBoard = board;
    minimax(tempBoard, 0, true);
    cout << "Minimax calls without Alpha-Beta Pruning: " << cntMinimax << endl;

    cntAlphaBeta = 0;
    tempBoard = board;
    alphaBeta(tempBoard, 0, INT_MIN, INT_MAX, true);
    cout << "Minimax calls with Alpha-Beta Pruning: " << cntAlphaBeta << endl;

    cout << "Alpha-Beta Pruning reduced calls by: "
         << cntMinimax - cntAlphaBeta << " (" << ((cntMinimax - cntAlphaBeta) * 100.0 / cntMinimax) << "% reduction)"
         << endl;

    return 0;
}
