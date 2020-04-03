#include <vector>

#include "test_framework/generic_test.h"

using std::vector;

vector<int> PlusOne(vector<int> A) {
    int carry = 1;

    for (int i = A.size() - 1; i >= 0; --i) {
        A[i] += carry;
        if (10 <= A[i]) {
            A[i] = 0;
            carry = 1;
            continue;
        }
        carry = 0;
    }

    vector<int> rv;
    if (carry) {
        rv.push_back(carry);
    }
    rv.insert(rv.end(), A.begin(), A.end());

    return rv;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"A"};
    return GenericTestMain(args, "int_as_array_increment.cc",
                           "int_as_array_increment.tsv", &PlusOne,
                           DefaultComparator{}, param_names);
}
