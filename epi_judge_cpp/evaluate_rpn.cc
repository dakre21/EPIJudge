#include <functional>
#include <unordered_map>
#include <string>
#include <stack>

#include "test_framework/generic_test.h"

using namespace std;

int Evaluate(const string& expression) {
    stack<int> numbers;
    stringstream ss(expression);
    string token = "";

    const unordered_map<string, function<int(int, int)>> kOperators = {
        { "+", [](int x, int y) { return x + y; } },
        { "-", [](int x, int y) { return x - y; } },
        { "*", [](int x, int y) { return x * y; } },
        { "/", [](int x, int y) { return x / y; } },
    };

    while (getline(ss, token, ',')) {
        if (kOperators.count(token)) {
            const int y = numbers.top();
            numbers.pop();
            const int x = numbers.top();
            numbers.pop();
            numbers.emplace(kOperators.at(token)(x, y));
        } else {
            numbers.emplace(stoi(token));
        }
    }

    return numbers.top();
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"expression"};
    return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
                           DefaultComparator{}, param_names);
}
