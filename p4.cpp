#include <iostream>
#include <vector>
using namespace std;

int N;

// Function to print solution
void printBoard(vector<int> &board) {
    cout << "\nSolution:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i] == j)
                cout << "Q ";
            else
                cout << ". ";
        }
        cout << endl;
    }
}

// Check if safe (Constraint checking)
bool isSafe(int row, int col, vector<int> &board) {
    for (int i = 0; i < row; i++) {
        int prevCol = board[i];

        // Same column
        if (prevCol == col)
            return false;

        // Diagonals
        if (abs(prevCol - col) == abs(i - row))
            return false;
    }
    return true;
}

// Backtracking function
bool solve(int row, vector<int> &board) {
    if (row == N) {
        printBoard(board);
        return true; // one solution
    }

    for (int col = 0; col < N; col++) {

        // Branch & Bound pruning
        if (isSafe(row, col, board)) {

            board[row] = col; // place queen

            if (solve(row + 1, board))
                return true;
        }
    }
    return false;
}

int main() {
    cout << "Enter number of queens: ";
    cin >> N;

    vector<int> board(N, -1);

    if (!solve(0, board))
        cout << "No solution exists.\n";

    return 0;
}