
#include <array>
#include <bitset>
#include "utils.h"

#include <ranges>

using namespace std;

struct monkey
{
    std::vector<int> items;
    std::function<int(int)> op;
    int test = 1;
    monkey* on_true = nullptr;
    monkey* on_false = nullptr;
    int on_true_index = 0;
    int on_false_index = 0;

    size_t total_inspected = 0u;

    void turn() {
        total_inspected += items.size();
        for (auto v : items) {
            auto w = op(v);
            w /= 3;
            if (0 == (w % test)) {
                on_true->items.push_back(w);
            }
            else {
                on_false->items.push_back(w);
            }
        }
        items.clear();
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


    auto* m = &monkeys[0];
    while (!f.empty()) {
        f.line(); // monkey number
        auto starting = getline_after_colon();        
        while (!starting.empty()) {
            auto v = starting.split(',').parseInt64();
            m->items.push_back(v);
        }
        auto op = getline_after_colon();
        op.split();
        op.split();
        op.split();
        auto opc = op.split()[0];
        op.trim();
        auto opval = op.parseInt64();
        if (opc == '+') {
            if (op == "old") {
                m->op = [=](int v) { return v + v; };
            }
            else {
                m->op = [=](int v) { return v + opval; };
            }
        }
        else if (opc == '*') {
            if (op == "old") {
                m->op = [=](int v) { return v * v; };
            }
            else {
                m->op = [=](int v) { return v * opval; };
            }
        }

        auto test = getline_after_colon();
        test.split();
        test.split();
        m->test = test.parseInt64();


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

    for (auto i : integers(20)) {
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
    
    part1 = sorted[0]->total_inspected * sorted[1]->total_inspected;

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