

#include "utils.h"

using namespace std;


struct Value {
    int v = -1;
    std::vector<Value> vec;

    void parse(StringView& s) {
        if (s.startsWith('[')) {
            s.pop_front();
            while (!s.startsWith(']')) {
                assert(!s.empty());
                vec.push_back({});
                vec.back().parse(s);
                if (s.startsWith(',')) {
                    s.pop_front();
                }
            }
            s.pop_front();
        }
        else {
            auto pos = s.find_first_of(",]");
            assert(pos != s.npos);
            v = (int) s.left(pos).parseInt64();
            if (s[pos] == ',') {
                s.splitAtSeparatorPos(pos);
            }
            else {
                s = s.mid(pos);
            }
        }
    }

    bool isInteger() const {
        return (v > -1);
    }
    void convertToList() {
        vec.push_back(*this);
        v = -1;
    }
    int compare(Value& other) {
        if (isInteger()) {
            if (other.isInteger()) {
                // both integers
                if (v < other.v) {
                    return -1;
                }
                if (v == other.v) {
                    return 0;
                }
                return 1;
            }
            else {
                convertToList();
            }
        }
        else {
            if (other.isInteger()) {
                other.convertToList();
            }
        }
        // list-list compare
        for (auto i : integers(vec.size())) {
            if (i >= other.vec.size()) {
                return 1; // If the right list runs out of items first, the inputs are not in the right order.
            }
            auto c = vec[i].compare(other.vec[i]);
            if (c != 0) {
                return c;
            }
        }
        if (vec.size() == other.vec.size()) {
            return 0;
        }
        return -1;
    }
};

//-----------------------------------------------------------------------------
void solveFile(char const* fname) {
    auto input = FileReadAll(fname);
    StringView f(input);
    f = f.rightTrimmed();

    uint64_t part1 = 0;
    uint64_t part2 = 0;

    uint32_t pair_index = 1;

    std::vector<Value> all;

    while (!f.empty()) {
        auto a = f.line();
        auto b = f.line();
        f.line(); // skip blank

        Value va;
        Value vb;
        va.parse(a);
        vb.parse(b);

        all.push_back(va);
        all.push_back(vb);

        if (va.compare(vb) < 1) {
            part1 += pair_index;
        }

        ++pair_index;
    }
    auto divastr = StringView("[[2]]");
    auto divbstr = StringView("[[6]]");
    Value diva;
    Value divb;
    diva.parse(divastr);
    divb.parse(divbstr);

    std::vector<Value*> order;
    for (auto& v : all) {
        order.push_back(&v);
    }

    order.push_back(&diva);
    order.push_back(&divb);

    std::sort(order.begin(), order.end(), [&](Value const* a, Value const* b) {
        auto ca = *a;
        auto cb = *b; // copy as compare can mutate
        return (ca.compare(cb) < 0);
    });

    auto diva_index = index_of(order, &diva);
    auto divb_index = index_of(order, &divb);

    part2 = (diva_index + 1) * (divb_index + 1);

    print(part1);

    print(part2);
}

//-----------------------------------------------------------------------------
int main() {
    using Clock = chrono::high_resolution_clock;

    print("example");
    solveFile("example.txt");

    auto start = Clock::now();
    print("input");
    solveFile("input.txt");
    auto end = Clock::now();
    std::cout << chrono::duration_cast<chrono::microseconds>(end - start).count() << "uS" << std::endl;

    return 0;
}