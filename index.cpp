#include <iostream>
#include <vector>
using namespace std;

#define LEN 9 // LEN represents the size of our Sudoku grid

// Function to check if placing 'val' at (row, col) is valid
bool is_possible(vector<vector<int>>& board, int row, int col, int val) {
    // Check if 'val' already exists in the current column
    for (int i = 0; i < LEN; i++) {
        if (board[i][col] == val) {
            return false;
        }
    }

    // Check if 'val' already exists in the current row
    for (int i = 0; i < LEN; i++) {
        if (board[row][i] == val) {
            return false;
        }
    }

    // Check if 'val' already exists in the 3x3 subgrid
    int startRow = 3 * (row / 3);   // Calculate starting row index of the 3x3 grid
    int startCol = 3 * (col / 3);   // Calculate starting column index of the 3x3 grid

    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if (board[i][j] == val) {
                return false;
            }
        }
    }

    // If all checks pass, the placement is valid
    return true;
}

// Recursive function to solve the Sudoku puzzle
bool solve(vector<vector<int>>& board, int row, int col) {
    // Move to the next row and reset column if end of the current row is reached
    if (col == LEN) {
        col = 0;
        row++;
        if (row == LEN) {
            return true; // Puzzle solved successfully
        }
    }

    // Skip already filled cells
    if (board[row][col] != 0) {
        return solve(board, row, col + 1);
    }

    // Try placing numbers from 1 to 9
    for (int num = 1; num <= LEN; num++) {
        if (is_possible(board, row, col, num)) {
            board[row][col] = num;
            if (solve(board, row, col + 1)) {
                return true;
            }
            board[row][col] = 0; // Backtrack if placing 'num' doesn't work
        }
    }

    return false; // No valid number found, backtrack
}

// Function to print the Sudoku board
void print_board(const vector<vector<int>>& board) {
    for (int row = 0; row < LEN; ++row) {
        for (int col = 0; col < LEN; ++col) {
            cout << board[row][col] << " ";
            if ((col + 1) % 3 == 0 && col < LEN - 1) {
                cout << "| ";
            }
        }
        cout << endl;
        if ((row + 1) % 3 == 0 && row < LEN - 1) {
            cout << "------+-------+------" << endl;
        }
    }
}

int main() {
    vector<vector<int>> sudokuBoard = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "Sudoku Grid:" << endl;
    print_board(sudokuBoard);

    bool solved = solve(sudokuBoard, 0, 0);
    
    if (solved) {
        cout << "\nSolved Sudoku:" << endl;
        print_board(sudokuBoard);
    } else {
        cout << "\nNo solution exists." << endl;
    }

    return 0;
}
