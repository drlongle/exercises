CXX     := g++
CXXFLAGS := -Wall -Wextra -pedantic -Wno-unused-parameter -fno-strict-aliasing -g

all: tetris test

tetris: Main.o TetrisEngine.o
	$(CXX) -o $@ Main.o TetrisEngine.o

test: Test.o TetrisEngine.o
	$(CXX) -o $@ Test.o TetrisEngine.o

.cpp.o:
	${CXX} -c ${CXXFLAGS} $<

clean:
	rm -f tetris test *.o a.out *~

