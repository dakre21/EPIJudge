#include <string>
#include <numeric>
#include <cmath>

#include "test_framework/generic_test.h"

using std::string;
using std::reverse;

string ConvertBase(const string& num_as_string, int b1, int b2) {
    int start = 0;
    string result = "";
    if (num_as_string[0] == '-') {
        start = 1;
    }

    int num = 0;
    for (int i = start; i < num_as_string.size(); ++i) {
        int tmp = 0;
        if (isdigit(num_as_string[i])) {
            tmp = num_as_string[i] - '0';
        } else {
            tmp = num_as_string[i] - 'A' + 10;
        }
        num += tmp * pow(b1, num_as_string.size() - 1 - i);
    }

    do {
        int remainder = abs(num % b2);
        char tmp;
        if (remainder < 10) {
            tmp = '0' + remainder;
        } else {
            tmp = 'A' + remainder - 10;
        }
        result.push_back(tmp);
        num /= b2;
    } while (num);

    if (start) {
        result.push_back('-');
    }

    reverse(result.begin(), result.end());
    return result;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
    return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                           &ConvertBase, DefaultComparator{}, param_names);
}
