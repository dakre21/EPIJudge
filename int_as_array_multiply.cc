#include <cmath>
#include <vector>

#include "test_framework/generic_test.h"

using std::vector;

vector<int> Multiply(vector<int> num1, vector<int> num2) {
    unsigned long long total = 0;
    unsigned negative = 0;

    if (num1[0] < 0) {
        num1[0] *= -1;
        negative ^= 1;
    }
    if (num2[0] < 0) {
        num2[0] *= -1;
        negative ^= 1;
    }

    int i = 0;
    for (auto one : num1) {
        i++;
        if (0 == one) {
            continue;
        }
        int j = 0;
        for (auto two : num2) {
            total += (one * pow(10, num1.size() - i)) * (two * pow(10, num2.size() - ++j));
        }
    }

    vector<int> rv;
    while (total) {
        rv.push_back(total % 10);
        total /= 10;
    }

    vector<int> rv;
    int i = 0;
    while (total) {
        rv.push_back(total % 10);
        total /= 10;
    }

    std::reverse(rv.begin(), rv.end());

    if (negative) {
        rv[rv.size() - 1] *= -1;
    }

    return rv;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"num1", "num2"};
    return GenericTestMain(args, "int_as_array_multiply.cc",
                           "int_as_array_multiply.tsv", &Multiply,
                           DefaultComparator{}, param_names);
}
