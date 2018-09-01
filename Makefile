CXX = g++
CXXFLAGS = -Wall -Werror -pedantic --std=c++11 -g

main.exe: main.cpp Game.cpp Arena.cpp Player.cpp Pod.cpp Unit.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

Arena_tests.exe: Arena_tests.cpp Arena.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

Unit_tests.exe: Unit_tests.cpp Unit.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

Pod_tests.exe: Pod_tests.cpp Pod.cpp Unit.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

Player_tests.exe: Player_tests.cpp Player.cpp Unit.cpp Pod.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

Game_tests.exe: Game_tests.cpp Game.cpp Player.cpp Unit.cpp Pod.cpp Arena.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -vrf *.o *.exe *.gch *.dSYM *.stackdump *.out.txt
