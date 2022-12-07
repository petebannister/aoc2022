#include <bitset>
#include "utils.h"

using namespace std;

int priority(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return ((ch - 'a') + 1);
    }
    if (ch >= 'A' && ch <= 'Z') {
        return ((ch - 'A') + 27);
    }
    return 0;
}

//-----------------------------------------------------------------------------
void solveFile(char const* fname) {
    TextFileIn f(fname);

    uint64_t part1 = 0;
    uint64_t part2 = 0;

    using Set = std::bitset<53>;

    Set badge[3];
    int g = 0;

    for (auto line : f.lines()) {
        if (line.empty()) {
            break;
        }
        auto a = line.left(line.size() / 2);
        auto b = line.right(line.size() / 2);
        Set s;
        for (auto c : a) {
            auto p = priority(c);
            s.set(p, true);
            badge[g].set(p, true);
        }
        for (auto c : b) {
            auto p = priority(c);
            if (s[p]) {
                part1 += p;
                break;
            }
        }
        for (auto c : b) {
            auto p = priority(c);
            badge[g].set(p, true);
        }

        ++g;
        if (g == 3) {
            g = 0;
            auto intersection = badge[0] & badge[1] & badge[2];
            for (auto i : integers(intersection.size())) {
                if (intersection[i]) {
                    part2 += i;
                    break;
                }
            }
            badge[0] = {};
            badge[1] = {};
            badge[2] = {};
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