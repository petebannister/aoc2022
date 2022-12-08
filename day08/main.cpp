
#include <array>
#include <bitset>
#include "utils.h"

using namespace std;

using Grid = std::vector<std::vector<uint16_t>>;

//-----------------------------------------------------------------------------
void solveFile(char const* fname) {
    TextFileIn f(fname);

    uint64_t part1 = 0;
    uint64_t part2 = 0;

    Grid grid;
    grid.reserve(512);    

    Grid occlusion;

    for (auto line : f.lines()) {
        if (line.empty()) {
            break;
        }
        grid.push_back({});
        occlusion.push_back({});
        auto& row = grid.back();
        row.reserve(line.size());
        for (auto c : line) {
            row.push_back(narrow_cast<uint8_t>(c - '0') + 1);
            occlusion.back().push_back(10);
        }
    }

    auto const rows = grid.size();
    auto const cols = grid[0].size();

    uint8_t h1, h2;
    for (auto y : integers(rows)) {
        h1 = 0;
        h2 = 0;
        for (auto x : integers(cols)) {
            auto x2 = (cols - x) - 1;
            amin(occlusion[y][x], h1);
            amax(h1, grid[y][x]);

            amin(occlusion[y][x2], h2);
            amax(h2, grid[y][x2]);
        }
    }

    for (auto x : integers(cols)) {
        h1 = 0;
        h2 = 0;
        for (auto y : integers(rows)) {
            auto y2 = (rows - y) - 1;
            amin(occlusion[y][x], h1);
            amax(h1, grid[y][x]);

            amin(occlusion[y2][x], h2);
            amax(h2, grid[y2][x]);
        }
    }

    //print(occlusion);

    for (auto y : integers(rows)) {
        for (auto x : integers(cols)) {
            if (grid[y][x] > occlusion[y][x]) {
                ++part1;
            }
        }
    }

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