#include <algorithm>
#include <vector>

#include "test_framework/generic_test.h"

using std::vector;

double BuyAndSellStockOnce(const vector<double>& prices) {
    if (prices.empty()) {
        return 0;
    }

    double profit = 0, min = *prices.begin();
    auto it = prices.begin() + 1;
    for (; it != prices.end(); ++it) {
        min = fmin(min, *it);
        profit = fmax(profit, (*it - min));
    }
    return profit;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"prices"};
    return GenericTestMain(args, "buy_and_sell_stock.cc",
                           "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                           DefaultComparator{}, param_names);
}
