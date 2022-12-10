
#include <array>
#include <bitset>
#include "utils.h"

#include <ranges>

using namespace std;

template <int N>
struct pipeline
{
    std::array<int64_t, N> a = { 0 };

    int64_t next() {
        auto v = a[0];
        for (auto i : integers(N - 1)) {
            a[i] = a[i + 1];
        }
        a[N - 1] = 0;
        return v;
    }
    void push(int64_t v) {
        a[N - 1] = v;
    }
};

//-----------------------------------------------------------------------------
void solveFile(char const* fname) {
    auto input = FileReadAll(fname);
    StringView f(input);
    f = f.rightTrimmed();

    uint64_t part1 = 0;
    uint64_t part2 = 0;

    pipeline<2> addx;
    int64_t x = 1;
    int64_t cycle = 1;

    auto exec = [&] {
        if (cycle >= 20) {
            if (0 == ((cycle - 20) % 40)) {
                part1 += x * cycle;
            }
        }

        x += addx.next();
        ++cycle;
    };

    while (!f.empty()) {
        auto line = f.line();
        auto ins = line.split();
        auto op = line.split();
        auto opint = op.parseInt64();
        if (ins == "noop") {
            exec();
        }
        else if (ins == "addx") {
            addx.push(opint);
            exec();
            exec();
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