#include <iostream>
#include <vector>

#define N 9 // Sudoku size (9x9)

// Function to print the Sudoku board
void printBoard(const std::vector<std::vector<int>>& board) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            std::cout << board[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

// Function to check if a number can be placed at board[row][col]
bool isSafe(const std::vector<std::vector<int>>& board, int row, int col, int num) {
    // Check the row and column
    for (int x = 0; x < N; x++) {
        if (board[row][x] == num || board[x][col] == num) {
            return false;
        }
    }

    // Check the 3x3 sub-grid
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku board using backtracking
bool solveSudoku(std::vector<std::vector<int>>& board) {
    int row, col;
    bool isEmpty = false;

    // Find an empty space (denoted by 0)
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (board[row][col] == 0) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) {
            break;
        }
    }

    // If no empty space is found, the board is solved
    if (!isEmpty) {
        return true;
    }

    // Try placing numbers from 1 to 9 in the empty space
    for (int num = 1; num <= 9; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;

            // Recursively solve the rest of the board
            if (solveSudoku(board)) {
                return true;
            }

            // If placing the number didn't lead to a solution, backtrack
            board[row][col] = 0;
        }
    }

    // Trigger backtracking
    return false;
}

int main() {
    std::vector<std::vector<int>> board = {
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

    if (solveSudoku(board)) {
        std::cout << "Sudoku solved successfully:" << std::endl;
        printBoard(board);
    } else {
        std::cout << "No solution exists for the given Sudoku." << std::endl;
    }

    return 0;
}
