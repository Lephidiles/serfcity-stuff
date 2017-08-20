CXX=g++
CPPFLAGS=-g3 -Wall -lsfml-graphics -lsfml-window -lsfml-system -std=c++17

SRC=main.cpp data.cpp
EXEC=frag

all:
	$(CXX) $(CPPFLAGS) $(SRC) -o $(EXEC)

clean:
	$(RM) $(EXEC)
