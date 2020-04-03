#include <vector>

#include "test_framework/generic_test.h"

using std::vector;

vector<vector<int>> GeneratePascalTriangle(int num_rows) {
    vector<vector<int>> result;
    for (int i = 0; i < num_rows; ++i) {
        vector<int> curr_row;
        for (int j = 0; j <= i; ++j) {
            if (0 == j || j == i) {
                curr_row.emplace_back(1);
            } else {
                curr_row.emplace_back(
                    result.back()[j - 1] + result.back()[j]
                );
            }
        }
        result.emplace_back(curr_row);
    }
    return result;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"num_rows"};
    return GenericTestMain(args, "pascal_triangle.cc", "pascal_triangle.tsv",
                           &GeneratePascalTriangle, DefaultComparator{},
                           param_names);
}
