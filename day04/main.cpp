
#include "utils.h"

using namespace std;

//-----------------------------------------------------------------------------
void solveFile(char const* fname) {
    TextFileIn f(fname);

    uint64_t part1 = 0;
    uint64_t part2 = 0;

    using Range = num_range<uint32_t>;

    Range a, b;

    for (auto line : f.lines()) {
        if (line.empty()) {
            break;
        }

        auto p = line;
        a.start_ = p.split('-').parseUInt64();
        a.limit_ = 1 + p.split(',').parseUInt64();

        b.start_ = p.split('-').parseUInt64();
        b.limit_ = 1 + p.parseUInt64();

        if (a.contains(b) || b.contains(a)) {
            ++part1;
        }
        if (a.intersects(b)) {
            ++part2;
        }
    }
    //assert(score > 10747);
    print(part1);

    print(part2);
}

//-----------------------------------------------------------------------------
int main() {
    print("example");
    solveFile("example.txt");
    print("input");
    solveFile("input.txt");
    
    return 0;
}