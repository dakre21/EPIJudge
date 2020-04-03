#include <algorithm>
#include <vector>

#include "test_framework/generic_test.h"

using namespace std;

vector<int> NextPermutation(vector<int> perm) {
    int k = perm.size() - 2;

    while (k >= 0 && perm[k] >= perm[k + 1]) {
        --k;
    }

    if (k < 0) {
        return {};
    }

    swap(
        *find_if(perm.rbegin(), perm.rend(), [&](int a) { return a > perm[k]; }),
        perm[k]
    );

    reverse(perm.begin() + k + 1, perm.end());
    return perm;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"perm"};
    return GenericTestMain(args, "next_permutation.cc", "next_permutation.tsv",
                           &NextPermutation, DefaultComparator{}, param_names);
}
