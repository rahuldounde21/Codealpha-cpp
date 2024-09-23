#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

const int N = 9;

// Function to check if a number is valid in a given row
bool isValidRow(vector<vector<int>>& board, int row, int num) {
    for (int col = 0; col < N; col++) {
        if (board[row][col] == num) {
            return false;
        }
    }
    return true;
}

// Function to check if a number is valid in a given column
bool isValidCol(vector<vector<int>>& board, int col, int num) {
    for (int row = 0; row < N; row++) {
        if (board[row][col] == num) {
            return false;
        }
    }
    return true;
}

// Function to check if a number is valid in a given 3x3 subgrid
bool isValidSubgrid(vector<vector<int>>& board, int startRow, int startCol, int num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[startRow + row][startCol + col] == num) {
                return false;
            }
        }
    }
    return true;
}

// Function to check if a number is valid in a given cell
bool isValid(vector<vector<int>>& board, int row, int col, int num) {
    return isValidRow(board, row, num) && isValidCol(board, col, num) && isValidSubgrid(board, row - row % 3, col - col % 3, num);
}

// Function to find the first empty cell (row, col) in the board
bool findEmptyCell(vector<vector<int>>& board, int& row, int& col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (board[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// Backtracking algorithm to solve the Sudoku puzzle
bool solveSudoku(vector<vector<int>>& board) {
    int row, col;

    if (!findEmptyCell(board, row, col)) {
        return true; // Puzzle is solved
    }

    for (int num = 1; num <= 9; num++) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num;

            if (solveSudoku(board)) {
                return true;
            }

            // If the current assignment leads to a dead-end, backtrack
            board[row][col] = 0;
        }
    }

    return false; // No solution found
}

// Function to print the solved Sudoku puzzle
void printSudoku(vector<vector<int>>& board) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to generate a Sudoku puzzle with a given difficulty level
vector<vector<int>> generateSudoku(int difficulty) {
    vector<vector<int>> board(N, vector<int>(N, 0));
    solveSudoku(board);

    // Remove cells based on the difficulty level
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(1, N * N);

    int cellsToRemove = difficulty * N * N / 10;
    for (int i = 0; i < cellsToRemove; i++) {
        int row = distribution(generator) % N;
        int col = distribution(generator) % N;
        board[row][col] = 0;
    }

    return board;
}

int main() {
    int difficulty;
    cout << "Enter difficulty level (1-9): ";
    cin >> difficulty;

    vector<vector<int>> puzzle = generateSudoku(difficulty);

    cout << "Generated Sudoku puzzle:\n";
    printSudoku(puzzle);

    if (solveSudoku(puzzle)) {
        cout << "Solved Sudoku puzzle:\n";
        printSudoku(puzzle);
    } else {
        cout << "No solution found.\n";
    }

    return 0;
}