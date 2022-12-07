
#include <array>
#include <bitset>
#include "utils.h"

using namespace std;

//-----------------------------------------------------------------------------
void solveFile(char const* fname) {
    TextFileIn f(fname);

    uint64_t part1 = 0;
    uint64_t part2 = 0;

    std::array<char, 4> buffer;
    std::bitset<127> s;

    for (auto line : f.lines()) {
        if (line.empty()) {
            break;
        }
        auto pos = 0;

        for (auto c : line) {
            buffer[pos % 4] = c;
            if (pos > 2) {
                s = {};
                s.set(buffer[0], true);
                s.set(buffer[1], true);
                s.set(buffer[2], true);
                s.set(buffer[3], true);
                if (s.count() == 4) {
                    part1 = pos + 1;
                    break;
                }
            }
            ++pos;
        }

        print(part1); // part 1
    }
}

//-----------------------------------------------------------------------------
int main() {
    print("example");
    solveFile("example.txt");
    print("input");
    solveFile("input.txt");
    
    return 0;
}