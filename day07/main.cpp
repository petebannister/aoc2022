
#include <array>
#include <bitset>
#include "utils.h"

using namespace std;

struct file {
    std::string name;
    uint64_t size = 0;
};
struct dir {
    std::string name;
    dir* parent = nullptr;
    uint64_t size = 0;
    std::map<std::string, file, std::less<>> files;
    std::map<std::string, dir, std::less<>> dirs;

    void addSize(uint64_t n) {
        size += n;
        if (parent) {
            parent->addSize(n);
        }
    }

    uint64_t part1() {
        uint64_t r = 0;
        if (size <= 100000u) {
            r += size;
        }
        for (auto& d : dirs) {
            r += d.second.part1();
        }
        return r;
    }

    void dirsAtLeast(uint64_t at_least, std::vector<dir const*>& out) {
        if (size >= at_least) {
            out.push_back(this);
            for (auto& d : dirs) {
                d.second.dirsAtLeast(at_least, out);
            }
        }
    }
};

//-----------------------------------------------------------------------------
void solveFile(char const* fname) {
    TextFileIn f(fname);

    uint64_t part1 = 0;
    uint64_t part2 = 0;
    
    dir root = { "/" };

    auto iline = f.lines().begin();
    auto const eline = f.lines().end();

    bool is_list = false;

    dir* cwd = &root;
    for (auto line : f.lines()) {
        if (line.startsWith('$')) {
            is_list = false;
            line.split(' ');
            auto cmd = line.split(' ');
            if (0 == cmd.compare("cd")) {
                if (0 == line.compare("/")) {
                    cwd = &root;
                }
                else if (0 == line.compare("..")) {
                    if (cwd->parent) {
                        cwd = cwd->parent;
                    }
                }
                else if (auto* d = map_value(cwd->dirs, line)) {
                    cwd = d;
                }
                else {
                    auto* p = cwd;
                    cwd = &cwd->dirs[line.toString()];
                    cwd->name = line.toString();
                    cwd->parent = p;
                }                
            }
            else if (0 == cmd.compare("ls")) {
                is_list = true;
            }
        }
        else if (is_list) {
            auto a = line.split(' ');
            auto name = line.split(' ');
            if (0 == a.compare("dir")) {
                auto& d = cwd->dirs[name.toString()];
                d.name = name.toString();
                d.parent = cwd;
            }
            else {
                auto size = a.parseUInt64();
                auto& f = cwd->files[name.toString()];
                if (f.size == 0) {
                    f.name = name.toString();
                    f.size = size;
                    cwd->addSize(size);
                }
            }
        }
    }

    part1 = root.part1();
    print(part1);

    auto unused = 70000000 - root.size;
    auto required = 30000000 - unused;
    std::vector<dir const*> dirs;
    root.dirsAtLeast(required, dirs);

    auto m = std::min_element(dirs.begin(), dirs.end(), [](dir const* a, dir const* b) {
        return (a->size < b->size);
    });
    
    part2 = (*m)->size;
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