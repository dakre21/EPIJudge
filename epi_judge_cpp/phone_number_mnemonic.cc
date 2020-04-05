#include <string>
#include <vector>
#include <array>

#include "test_framework/generic_test.h"

using std::string;
using std::vector;
using std::array;

const int kNumTelDigits = 10;

const array<string, kNumTelDigits> kMapping = {
    { "0", "1", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ" }
};

void PhoneMnemonicHelper(const string& phone_number, int digit, 
                         string& partial_mnemonic, 
                         vector<string>& mnemonics) {
    if (phone_number.size() == digit) {
        mnemonics.emplace_back(partial_mnemonic);
    } else {
        for (auto c : kMapping[phone_number[digit] - '0']) {
            partial_mnemonic[digit] = c;
            PhoneMnemonicHelper(phone_number, digit + 1, partial_mnemonic, 
                                mnemonics);
        }
    }
}

vector<string> PhoneMnemonic(const string& phone_number) {
    string partial_mnemonic(phone_number.size(), 0);
    vector<string> mnemonics;
    PhoneMnemonicHelper(phone_number, 0, partial_mnemonic, mnemonics);
    return mnemonics;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"phone_number"};
    return GenericTestMain(args, "phone_number_mnemonic.cc",
                           "phone_number_mnemonic.tsv", &PhoneMnemonic,
                           UnorderedComparator{}, param_names);
}
