#include <iostream>

#include "TetrisEngine.h"

using namespace std;

int main(int argc, const char **argv) {
    TetrisEngine engine(10);
    std::string line;
    while (getline(std::cin, line)) {
        engine.process_line(line);
        std::cout << engine.get_height() << std::endl;
    }

    return 0;
}
