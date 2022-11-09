#include <iostream>
#include <string>
#include <vector>

#include "TetrisEngine.h"

using namespace std;

std::vector<std::pair<string, size_t>> test_cases{
    {"Q0", 2},
    {"Q0,Q1", 4},
    {"Q0,Q2,Q4,Q6,Q8", 0},
    {"Q0,Q2,I4,Q8", 1},
    {"Q0,Q2,S4,Z6,Q8", 4},
    {"Q0,Q2,Q4,Q6,Q8,Q1", 2},
    {"Q0,Q2,Q4,Q6,Q8,Q1,Q1", 4},
    {"I0,I4,Q8", 1},
    {"I0,I4,Q8,I0,I4", 0},
    {"L0,J2,L4,J6,Q8", 2},
    {"L0,Z1,Z3,Z5,Z7", 2},
    {"T0,T3", 2},
    {"T0,T3,I6,I6", 1},
    {"I0,I6,S4", 1},
    {"T1,Z3,I4", 4},
    {"L0,J3,L5,J8,T1", 3},
    {"L0,J3,L5,J8,T1,T6", 1},
    {"L0,J3,L5,J8,T1,T6,J2,L6,T0,T7", 2},
    {"L0,J3,L5,J8,T1,T6,J2,L6,T0,T7,Q4", 1},
    {"S0,S2,S4,S6", 8},
    {"S0,S2,S4,S5,Q8,Q8,Q8,Q8,T1,Q1,I0,Q4", 8},
    {"L0,J3,L5,J8,T1,T6,S2,Z5,T0,T7", 0},
    {"Q0,I2,I6,I0,I6,I6,Q2,Q4", 3},
    {"L0,J8,I0,I6,Q4,Q2,Q4", 5},
    {"L0,J8,I0,I6,Q4,Q1,Q1,Q4", 7},
    {"L0,J8,I0,I6,Q4,L2,L2,Q4", 9},
    {"L0,J8,I0,I6,Q4,L2,L2,T7,T7,T7,T7,Q4", 11},
    {"L0,J8,I0,I0,L0,L0,L0,I6,I6,J8,J8,J8,Q4,Q4,Q4", 12},
    {"Z0,S7,I0,I0,I6,I6,Q4,L2,L2,Q4", 8}};

int main(int argc, const char **argv) {
    TetrisEngine engine(10);
    size_t nr_test_cases{0}, test_passed{0}, test_failed{0};
    for (auto &test_case : test_cases) {
        ++nr_test_cases;
        engine.process_line(test_case.first);
        auto result = engine.get_height();
        if (result != test_case.second) {
            ++test_failed;
            std::cerr << "Test case " << test_case.first
                      << " fails. Expected result is " << test_case.second
                      << " but got " << result << endl;
        } else {
            ++test_passed;
        }
    }

    std::cout << "Number of test cases: " << nr_test_cases << std::endl;
    std::cout << "Number of passed test cases: " << test_passed << std::endl;
    std::cout << "Number of failed test cases: " << test_failed << std::endl;

    return 0;
}
