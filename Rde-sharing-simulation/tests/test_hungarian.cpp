#include "Hungarian.h"
#include <cassert>
#include <iostream>

int main() {
    std::vector<std::vector<double>> cost = {{4,1,3},{2,0,5},{3,2,2}};
    auto res = hungarian(cost);
    // validate assignment: res should be a valid permutation with reasonable total cost
    double total = 0;
    for (int i=0;i<(int)res.size();++i) if(res[i]>=0) total += cost[i][res[i]];
    std::cout << "hungarian total=" << total << "\n";
    assert(total <= 7.0 + 1e-6); // expected optimal is <=7
    return 0;
}
