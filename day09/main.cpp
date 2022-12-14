
#include <array>
#include <bitset>
#include "utils.h"

#include <ranges>

using namespace std;

bool touching(Point a, Point b) {
    auto d = a - b;
    return (abs(d.x) <= 1) && (abs(d.y) <= 1);
}

void move(Point& T, Point& H) {

    if (!touching(H, T)) {
        if (T.y == H.y) {
            if (T.x < H.x) {
                T.x = H.x - 1;
            }
            else {
                T.x = H.x + 1;
            }
        }
        else if (T.x == H.x) {
            if (T.y < H.y) {
                T.y = H.y - 1;
            }
            else {
                T.y = H.y + 1;
            }
        }
        else {
            if (T.x < H.x) {
                ++T.x;
            }
            else {
                --T.x;
            }

            if (T.y < H.y) {
                ++T.y;
            }
            else {
                --T.y;
            }
        }
    }
}

//-----------------------------------------------------------------------------
void solveFile(char const* fname) {
    TextFileIn f(fname);

    uint64_t part1 = 0;
    uint64_t part2 = 0;

    Point H;
    Point T;

    array<Point, 10> rope = { {} };

    std::unordered_map<char, Point> m;
    m['R'] = { 1, 0 };
    m['U'] = { 0, -1 };
    m['L'] = { -1, 0 };
    m['D'] = { 0, 1 };

    std::set<Point> visited;
    std::set<Point> visited2;

    visited.insert(T);
    visited2.insert(T);

    for (auto line : f.lines()) {
        if (line.empty()) {
            break;
        }
        auto dir = m[line[0]];
        line.split(' ');        
        auto n = line.parseInt64();
        while (n--) {
            H += dir;

            rope.front() += dir;

            move(T, H);
            visited.insert(T);

            for (auto k : integers(rope.size() - 1)) {
                move(rope[k + 1], rope[k]);
            }
            visited2.insert(rope.back());
        }
        

    }

    part1 = visited.size();
    part2 = visited2.size();
    //assert(part1 == 6339);
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