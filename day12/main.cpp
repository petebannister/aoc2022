
#include <array>
#include <bitset>
#include "utils.h"

using namespace std;

//-----------------------------------------------------------------------------
void solveFile(char const* fname) {
    auto input = FileReadAll(fname);
    StringView f(input);
    f = f.rightTrimmed();

    uint64_t part1 = 0;
    uint64_t part2 = 0;

    vector<vector<char>> grid;
    while (!f.empty()) {
        auto line = f.line();
        if (!line.empty()) {
            grid.push_back(vector(line.begin(), line.end()));
        }
    }

    int rows = grid.size();
    int cols = grid[0].size();

    Point S;
    Point E;

    int y = 0;
    int x = 0;
    for (auto& row : grid) {
        x = 0;
        for (auto& v : row) {
            if (v == 'S') {
                S = { x, y };
            }
            if (v == 'E') {
                E = { x, y };
            }
            ++x;
        }
        ++y;
    }

    Bounds bounds;
    bounds.x_.limit_ = cols;
    bounds.y_.limit_ = rows;
    map<Point, int> steps;
    deque<Point> queue;
    queue.push_back(E);

    auto dirs = {
        Point(-1, 0),
        Point(0, -1),
        Point(1, 0),
        Point(0, 1),
    };

    steps[E] = 0;

    auto get = [&](Point const& p) -> char& {
        return grid[p.y][p.x];
    };
    get(E) = 'z';
    get(S) = 'a';

    auto can_go = [&](Point const& from, Point const& to) {
        auto fh = get(from);
        auto th = get(to);
        auto d = int(th) - int(fh);
        return (d <= 1);
    };

    while (!queue.empty()) {
        auto p = queue.front();
        queue.pop_front();
        for (auto& d : dirs) {
            auto next = p + d;
            if (bounds.contains(next)) {
                auto n = steps[p] + 1;
                if (!contains(steps, next)) {
                    if (can_go(next, p)) {
                        steps[next] = n;
                        queue.push_back(next);
                    }
                }
                else {
                    if (can_go(next, p)) {
                        auto& ns = steps[next];
                        if (ns > n) {
                            ns = n;
                            queue.push_back(next);
                        }
                    }
                }
            }
        }
    }
    part1 = steps[S];
        
    part2 = 0;

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