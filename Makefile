CXX=g++
CPPFLAGS=-g3 -Wall -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system

SRC=main.cpp data.cpp
EXEC=frag

all:
	$(CXX) $(CPPFLAGS) $(SRC) -o $(EXEC)

clean:
	$(RM) $(EXEC)
