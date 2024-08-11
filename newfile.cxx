#include <iostream>
#include <vector>

const int GRID_SIZE = 9;

void printGrid(const std::vector<std::vector<int>>& grid) {
    for (int row = 0; row < GRID_SIZE; ++row) {
        if (row % 3 == 0 && row != 0)
            std::cout << "---------------------\n";
        for (int col = 0; col < GRID_SIZE; ++col) {
            if (col % 3 == 0 && col != 0)
                std::cout << "| ";
            std::cout << grid[row][col] << " ";
        }
        std::cout << "\n";
    }
}

bool isValid(const std::vector<std::vector<int>>& grid, int row, int col, int num) {
    for (int x = 0; x < GRID_SIZE; ++x) {
        if (grid[row][x] == num || grid[x][col] == num ||
            grid[row - row % 3 + x / 3][col - col % 3 + x % 3] == num) {
            return false;
        }
    }
    return true;
}

bool solveSudoku(std::vector<std::vector<int>>& grid) {
    int row, col;
    bool emptyCellFound = false;
    for (row = 0; row < GRID_SIZE; ++row) {
        for (col = 0; col < GRID_SIZE; ++col) {
            if (grid[row][col] == 0) {
                emptyCellFound = true;
                break;
            }
        }
        if (emptyCellFound)
            break;
    }

    if (!emptyCellFound)
        return true;

    for (int num = 1; num <= GRID_SIZE; ++num) {
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid))
                return true;
            grid[row][col] = 0;
        }
    }
    return false;
}

void playSudoku() {
    std::vector<std::vector<int>> grid(GRID_SIZE, std::vector<int>(GRID_SIZE, 0));

    std::cout << "Enter the Sudoku grid (use 0 for empty cells):\n";
    for (int row = 0; row < GRID_SIZE; ++row) {
        for (int col = 0; col < GRID_SIZE; ++col) {
            std::cin >> grid[row][col];
        }
    }

    std::cout << "Initial Sudoku grid:\n";
    printGrid(grid);

    if (solveSudoku(grid)) {
        std::cout << "Solved Sudoku grid:\n";
        printGrid(grid);
    } else {
        std::cout << "No solution exists for the given Sudoku grid.\n";
    }
}

int main() {
    playSudoku();
    return 0;
}