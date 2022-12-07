#include <array>
#include "utils.h"

using namespace std;

//-----------------------------------------------------------------------------
void solveFile(char const* fname) {
    TextFileIn f(fname);


    auto iline = f.lines().begin();
    auto const eline = f.lines().end();

    std::array<std::vector<char>, 16> stacks;
    std::vector<char> tmpstack;

    // Read stacks
    for (; iline != eline; ++iline) {
        auto line = *iline;

        for (auto x = 0u; x < line.size(); x += 4u) {
            if (line[x] == '[') {
                stacks[x / 4u].push_back(line[x + 1u]);
            }
        }

        if (line.empty()) {
            break;
        }
    }
    for (auto& stack : stacks) {
        std::reverse(stack.begin(), stack.end());
    }

    auto stacks2 = stacks;

    if (iline != eline) {
        ++iline;
    }
    // Interpret commands
    for (; iline != eline; ++iline) {
        auto line = *iline;
        if (line.empty()) {
            break;
        }

        line.split(' ');
        auto n = line.split(' ').parseUInt64();
        line.split(' ');
        auto from = line.split(' ').parseUInt64();
        line.split(' ');
        auto to = line.parseUInt64();

        auto n2 = n; // for part 2
        while (n--) {
            auto crate = stacks[from-1].back();
            stacks[from-1].pop_back();
            stacks[to-1].push_back(crate);
        }

        // part2
        while (n2--) {
            auto crate = stacks2[from - 1].back();
            stacks2[from - 1].pop_back();
            tmpstack.push_back(crate);
        }
        while (!tmpstack.empty()) {
            stacks2[to - 1].push_back(tmpstack.back());
            tmpstack.pop_back();
        }
    }

    std::string part1;
    for (auto& stack : stacks) {
        if (!stack.empty()) {
            part1 += stack.back();
        }
    }
    print(part1);

    std::string part2;
    for (auto& stack : stacks2) {
        if (!stack.empty()) {
            part2 += stack.back();
        }
    }
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