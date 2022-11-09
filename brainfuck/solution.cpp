#include <algorithm>
#include <atomic>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <condition_variable>
#include <functional>
#include <future>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <ranges>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string_view>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

constexpr size_t datasize = 30'000;

void brainfuck(const std::string &instruction) {
    std::vector<char> cells(datasize, 0);
    int64_t isz = instruction.size();
    int64_t ip = 0; // instruction pointer
    int64_t dp = 0; // data pointer

    stack<int> open_brackets;
    map<int, int> forward, backward;
    for (ip = 0; ip < isz; ++ip) {
        char ch = instruction[ip];
        if (ch == '[')
            open_brackets.push(ip);
        else if (ch == ']') {
            forward[open_brackets.top()] = ip;
            backward[ip] = open_brackets.top();
            open_brackets.pop();
        }
    }

    for (ip = 0; ip < isz; ++ip) {
        switch (instruction[ip]) {
        case '>':
            if (++dp >= static_cast<int64_t>(datasize)) {
                throw std::invalid_argument(instruction);
            }
            break;
        case '<':
            if (--dp < 0) {
                throw std::invalid_argument(instruction);
            }
            break;
        case '+':
            ++cells[dp];
            break;
        case '-':
            --cells[dp];
            break;
        case '.':
            std::cout << cells[dp];
            break;
        case ',':
            std::cin >> cells[dp];
            break;
        case '[':
            if (cells[dp] == 0) {
                ip = forward[ip];
            }
            break;
        case ']':
            if (cells[dp] != 0) {
                ip = backward[ip];
            }
            break;
        }
    }
}

int main(int argc, char **argv) {
    std::string s = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+"
                    "++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";
    brainfuck(s);

    return 0;
}
