#include <vector>

#include "test_framework/generic_test.h"

using std::vector;

bool CheckRowAndColumn(const vector<vector<int>>& partial_assignment, 
        int row, int col) {
    for (size_t i = 0; i < partial_assignment.size(); ++i) {
        if (i == col || 0 == partial_assignment[row][i]) {
            continue;
        }
        if (partial_assignment[row][i] == partial_assignment[row][col]) {
            return false;
        }
    }

    for (size_t i = 0; i < partial_assignment.size(); ++i) {
        if (i == row || 0 == partial_assignment[i][col]) {
            continue;
        }
        if (partial_assignment[i][col] == partial_assignment[row][col]) {
            return false;
        }
    }
    return true;
}

bool CheckSubGrid(const vector<vector<int>>& partial_assignment, 
        int row, int col) {
    int start_row = 0, start_col = 0, end_row = 3, end_col = 3;
    if (3 <= row && row < 6) {
        start_row = 3, end_row = 6;
    } else if (6 <= row && row < 9) {
        start_row = 6, end_row = 9;
    }

    if (3 <= col && col < 6) {
        start_col = 3, end_col = 6;
    } else if (6 <= col && col < 9) {
        start_col = 6, end_col = 9;
    }

    for (int i = start_row; i < end_row; ++i) {
        for (int j = start_col; j < end_col; ++j) {
            if (i == row && j == col) {
                continue;
            }
            if (partial_assignment[i][j] == partial_assignment[row][col]) {
                return false;
            }
        }
    }
    return true;
}

// Check if a partially filled matrix has any conflicts.
bool IsValidSudoku(const vector<vector<int>>& partial_assignment) {
    for (size_t i = 0; i < partial_assignment.size(); ++i) {
        for (size_t j = 0; j < partial_assignment.size(); ++j) {
            if (!partial_assignment[i][j]){
                continue;
            }
            if (!CheckRowAndColumn(partial_assignment, i, j)) {
                return false;
            }
            if (!CheckSubGrid(partial_assignment, i, j)) {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"partial_assignment"};
    return GenericTestMain(args, "is_valid_sudoku.cc", "is_valid_sudoku.tsv",
                           &IsValidSudoku, DefaultComparator{}, param_names);
}
