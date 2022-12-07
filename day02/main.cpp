#include "utils.h"

using namespace std;

constexpr auto rock = 1;
constexpr auto paper = 2;
constexpr auto scissors = 3;
constexpr auto win = 6;
constexpr auto draw = 3;
constexpr auto lose = 0;



int score_one(int a, int b) {

    if (a == b) {
        return 3;
    }
    if (b == rock) {
        if (a == scissors) {
            return win;
        }
    }
    if (b == paper) {
        if (a == rock) {
            return win;
        }
    }
    if (b == scissors) {
        if (a == paper) {
            return win;
        }
    }
    return lose;
}


int choose(int a, int b) {
    if (b == 2) { // need to draw
        return a;
    }
    if (b == 3) { // need to win
        if (a == scissors) {
            return rock;
        }
        if (a == rock) {
            return paper;
        }
        return scissors;
    }
    // need to lose
    if (a == scissors) {
        return paper;
    }
    if (a == rock) {
        return scissors;
    }
    return rock;
}
//-----------------------------------------------------------------------------
void solveFile(char const* fname) {
    TextFileIn f(fname);

    uint64_t part1 = 0;
    uint64_t part2 = 0;

    for (auto line : f.lines()) {
        if (line.empty()) {
            break;
        }
        auto a = (line[0] - 'A') + 1; 
        auto b = (line[2] - 'X') + 1;

        uint32_t r = score_one(a, b);
        part1 += (b + r);

        auto choice = choose(a, b);

        part2 += (choice + score_one(a, choice));
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