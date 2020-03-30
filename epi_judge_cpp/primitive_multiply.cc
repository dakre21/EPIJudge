#include <iostream>

#include "test_framework/generic_test.h"

unsigned long long Add(unsigned long long x, unsigned long long y) {
    unsigned long long sum = 0, carryin = 0, k = 1, temp_a = x, temp_b = y;
    while (temp_a || temp_b) {
        unsigned long long ak = x & k, bk = y & k;
        unsigned long long carryout = (ak & bk) | (ak & carryin) | (bk & carryin);
        sum |= (ak ^ bk ^ carryin);
        carryin = carryout << 1, k <<= 1, temp_a >>= 1, temp_b >>= 1;
    }
    return sum | carryin;
}

unsigned long long Multiply(unsigned long long x, unsigned long long y) {
    unsigned long long sum = 0;
    while (x) {
        if (x & 1) {
            sum = Add(sum, y);
        }
        x >>= 1, y <<= 1;
    }
    return sum;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x", "y"};
    return GenericTestMain(args, "primitive_multiply.cc",
                           "primitive_multiply.tsv", &Multiply,
                           DefaultComparator{}, param_names);
}
