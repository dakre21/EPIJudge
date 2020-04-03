#include <algorithm>
#include <vector>

#include "test_framework/generic_test.h"

using std::vector;
using std::swap;

void ApplyPermutation(vector<int> perm, vector<int>* A_ptr) {
    vector<int>& A = *A_ptr;
    if (!A.size()) {
        return;
    }

    unsigned swap_pos = 0;
    while (swap_pos < perm.size() - 1) {
        if (perm[swap_pos] == swap_pos) {
            ++swap_pos;
            continue;
        }
        int value = perm[swap_pos];
        swap(perm[swap_pos], perm[value]);
        swap(A[swap_pos], A[value]);
    }
}

vector<int> ApplyPermutationWrapper(const vector<int>& perm, vector<int> A) {
    ApplyPermutation(perm, &A);
    return A;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"perm", "A"};
    return GenericTestMain(args, "apply_permutation.cc", "apply_permutation.tsv",
                           &ApplyPermutationWrapper, DefaultComparator{},
                           param_names);
}
