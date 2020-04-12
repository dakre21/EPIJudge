#include <string>

#include "test_framework/generic_test.h"

using std::string;

bool IsWellFormed(const string& s) {
    stack<char> left;
    for (int i = 0; i < s.size(); ++i) {
        if ('(' == s[i] || '{' == s[i] || '[' == s[i]) {
            left.emplace(s[i]);
            continue;
        }

        if (left.empty()) {
            return false;
        }

        if ((s[i] == ')' && left.top() != '(') ||
            (s[i] == '}' && left.top() != '{') ||
            (s[i] == ']' && left.top() != '[')) {
            return false;
        }
        left.pop();
    }
    return left.empty();
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"s"};
    return GenericTestMain(args, "is_valid_parenthesization.cc",
                           "is_valid_parenthesization.tsv", &IsWellFormed,
                           DefaultComparator{}, param_names);
}
