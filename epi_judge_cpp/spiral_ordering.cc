#include <vector>

#include "test_framework/generic_test.h"

using std::vector;

vector<int> MatrixInSpiralOrder(const vector<vector<int>>& square_matrix) {
    int size = square_matrix.size();
    int layers = size / 2;
    vector<int> spiral;
    for (int layer = 0; layer < layers; ++layer) {
        int row = layer, col = layer;
        for (; col < size - layer; ++col) {
            spiral.emplace_back(square_matrix[row][col]);
        }
        --col, ++row;
        for (; row < size - layer; ++row) {
            spiral.emplace_back(square_matrix[row][col]);
        }
        --row, --col;
        for (; col >= layer; --col) {
            spiral.emplace_back(square_matrix[row][col]);
        }
        --row, ++col;
        for (; row > layer; --row) {
            spiral.emplace_back(square_matrix[row][col]);
        }
    }
    if (size % 2) {
        spiral.emplace_back(square_matrix[layers][layers]);
    }
    return spiral;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"square_matrix"};
    return GenericTestMain(args, "spiral_ordering.cc", "spiral_ordering.tsv",
                           &MatrixInSpiralOrder, DefaultComparator{},
                           param_names);
}
