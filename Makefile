CXX = g++
CXXFLAGS = -Wall -Werror -pedantic --std=c++11 -g

all: game.cpp board.cpp piece.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -vrf *.o *.exe *.gch *.dSYM *.stackdump *.out.txt
