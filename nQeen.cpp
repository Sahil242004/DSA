#include <iostream>
#include <vector>
using namespace std;

// Function to print the chessboard
void printBoard(vector<vector<int>>& board, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << endl;
    }
    cout << endl;
}

// Function to check if placing a queen at board[row][col] is safe
bool isSafe(vector<vector<int>>& board, int row, int col, int N) {
    // Check column above
    for (int i = 0; i < row; i++)
        if (board[i][col]) return false;

    // Check upper-left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return false;

    // Check upper-right diagonal
    for (int i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j]) return false;

    return true;
}

// Recursive function to solve the N-Queens problem
bool solveNQueensUtil(vector<vector<int>>& board, int row, int N) {
    if (row >= N) return true; // All queens are placed successfully

    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col, N)) {
            board[row][col] = 1; // Place queen
            if (solveNQueensUtil(board, row + 1, N)) return true;
            board[row][col] = 0; // Backtrack
        }
    }
    return false; // No safe column found
}

// Function to solve the N-Queens problem
void solveNQueens() {
    int N;
    cout << "Enter the size of the chessboard (N): ";
    cin >> N;

    vector<vector<int>> board(N, vector<int>(N, 0));

    if (solveNQueensUtil(board, 0, N)) {
        cout << "Solution for " << N << "-Queens problem:\n";
        printBoard(board, N);
    } else {
        cout << "No solution exists for " << N << "-Queens problem.\n";
    }
}

int main() {
    solveNQueens();
    return 0;
}


// time complexity--> O(n!)
