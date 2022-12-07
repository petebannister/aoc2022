
#include <array>
#include <bitset>
#include "utils.h"

using namespace std;

template <int N>
size_t pos_distinct_n(StringView line) 
{
    std::array<char, N> buffer;
    std::bitset<127> s;

    auto pos = 0;

    for (auto c : line) {
        buffer[pos % N] = c;
        ++pos;
        if (pos >= N) {
            s = {};
            for (auto i : integers(N)) {
                s.set(buffer[i], true);
            }
            if (s.count() == N) {
                return pos;
            }
        }
    }
    return 0;
}

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
        auto part1 = pos_distinct_n<4>(line);
        print(part1);

        auto part2 = pos_distinct_n<14>(line);
        print(part2);
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