#include <iostream>

#include "test_framework/generic_test.h"

unsigned long long ReverseBits(unsigned long long x) {
    unsigned long long size = sizeof(x) * 8;
    for (unsigned long long i = 0; i < (size / 2); i++) {
        if (((x >> i) & 1) == ((x >> (size - i - 1)) & 1)) {
            continue;
        }
        x ^= (1L << i) | (1L << (size - i - 1));
    }
    return x;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x"};
    return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                           &ReverseBits, DefaultComparator{}, param_names);
}
