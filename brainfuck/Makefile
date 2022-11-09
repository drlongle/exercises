CXX     := g++
#CXXFLAGS := -Wall -Wextra -pedantic -Wno-unused-parameter -fno-strict-aliasing -std=c++20 -g -fsanitize=address -fsanitize=undefined -I..

CXXFLAGS := -Wall -Wextra -pedantic -Wno-unused-parameter -fno-strict-aliasing -std=c++20 -g 

all: solution

solution: solution.o
#$(CXX) -o $@ solution.o -ldl -pthread -lasan -lubsan
	$(CXX) -o $@ solution.o -ldl -pthread
.cpp.o:
	${CXX} -c ${CXXFLAGS} $<

clean:
	rm -f solution *.o a.out *~

