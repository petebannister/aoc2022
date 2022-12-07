#include "utils.h"

using namespace std;

//-----------------------------------------------------------------------------
void solveFile(char const* fname) {
    TextFileIn f(fname);

    std::vector<uint64_t> totals = {0};

    for (auto line : f.lines()) {
        totals.back() += line.parseUInt64();
        if (line.empty()) {
            totals.push_back(0u);
        }
    }

    auto imax = std::max_element(totals.begin(), totals.end());    

    auto const part1 = *imax;
    print(part1);

    std::sort(totals.begin(), totals.end(), std::greater<>());



    uint32_t part2 = totals[0] + totals[1] + totals[2];
    print(part2);
}

//-----------------------------------------------------------------------------
int main() {
    //print("example");
    //solveFile("example.txt");
    print("input");
    solveFile("input.txt");
    
    return 0;
}
