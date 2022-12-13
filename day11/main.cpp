
#include <array>
#include <bitset>
#include "utils.h"

#include <ranges>

using namespace std;

int divider;
//size_t round_number
int64_t initial_modulo = 0;
int64_t modulo = 0;

struct monkey
{
    size_t total_inspected = 0u;
    std::vector<int64_t> initial;
    std::vector<int64_t> items;
    std::function<int64_t(int64_t)> op;
    int test = 1;
    monkey* on_true = nullptr;
    monkey* on_false = nullptr;
    int on_true_index = 0;
    int on_false_index = 0;


    void turn() {
        total_inspected += items.size();
        for (auto v : items) {
            auto w = op(v);
            w /= divider;
            if (modulo != 0) {
                w %= modulo;
            }
            if (0 == (w % test)) {
                on_true->items.push_back(w);
            }
            else {
                on_false->items.push_back(w);
            }
        }
        items.clear();
    }
    void reset() {
        items = initial;
        total_inspected = 0;
    }
};

//-----------------------------------------------------------------------------
void solveFile(char const* fname) {
    auto input = FileReadAll(fname);
    StringView f(input);
    f = f.rightTrimmed();

    uint64_t part1 = 0;
    uint64_t part2 = 0;

    std::array<monkey, 32> monkeys;
    auto getline_after_colon = [&] {
        auto line = f.line();
        line.split(':');
        return line.trimmed();
    };

    initial_modulo = 0;

    auto* m = &monkeys[0];
    while (!f.empty()) {
        f.line(); // monkey number
        auto starting = getline_after_colon();
        while (!starting.empty()) {
            auto v = starting.split(',').parseInt64();
            m->initial.push_back(v);
        }
        auto op = getline_after_colon();
        op.split();
        op.split();
        op.split();
        auto opc = op.split()[0];
        op.trim();
        auto opval = op.parseInt64();

        auto test = getline_after_colon();
        test.split();
        test.split();

        auto testval = test.parseInt64();
        m->test = testval;

        if (initial_modulo == 0) {
            initial_modulo = testval;
        }
        else {
            initial_modulo *= testval;
        }

        if (opc == '+') {
            if (op == "old") {
                m->op = [=](auto v) { return v + v; };
            }
            else {
                m->op = [=](auto v) { return v + opval; };
            }
        }
        else if (opc == '*') {
            if (op == "old") {
                m->op = [=](auto v) { 
                    //modulo *= v;
                    return v * v; 
                };
            }
            else {
                m->op = [=](auto v) { 
                    return v * opval;
                };
            }
        }

        auto t = getline_after_colon();
        t.split();
        t.split();
        t.split();
        m->on_true_index = t.split().parseInt64();
        m->on_true = &monkeys[m->on_true_index];

        t = getline_after_colon();
        t.split();
        t.split();
        t.split();
        m->on_false_index = t.split().parseInt64();
        m->on_false = &monkeys[m->on_false_index];

        f.line(); // skip blank line
        ++m;
    }

    auto iterate = [&](size_t N) {
        modulo = initial_modulo;
        for (auto& m : monkeys) {
            m.reset();
        }
        for (auto i : integers(N)) {
            for (auto& m : monkeys) {
                m.turn();
            }
        }

        std::vector<monkey*> sorted;
        for (auto& m : monkeys) {
            sorted.push_back(&m);
        }
        std::sort(sorted.begin(), sorted.end(), [&](monkey* a, monkey* b) {
            return a->total_inspected > b->total_inspected;
            });

        //part1 = sorted[0]->total_inspected * sorted[1]->total_inspected;
        return sorted[0]->total_inspected * sorted[1]->total_inspected;
    };

    // part1
    divider = 3;
   // part1 = iterate(20);

    // part2
    divider = 1;

    part2 = iterate(1);
    part2 = iterate(20);
    part2 = iterate(1000);
    part2 = iterate(2000);

#if 0
    //limit = 1;
    //modulo = 1;
    part2 = 0;
    while (1) {
        if (10197 == iterate(20)) {
            int dbg = 0;
            break;
        }
        ++divider;
    }
    while (1) {
        if (27019168 == iterate(1000)) {
            int dbg = 0;
            break;
        }
        ++divider;
    }
    while (1) {
        if (2713310158 == iterate(10000)) {
            int dbg = 0;
            break;
        }
        ++divider;
    }
#endif
    
    //part1 = sorted[0]->total_inspected * sorted[1]->total_inspected;
    part2 = iterate(10000);

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