CXX = g++
SOURCES = Main.cpp Game.cpp World.cpp Entity.cpp
EXE = build/run
PROJECT_ROOT = $(shell pwd)

all: $(EXE)
	./$(EXE)

$(EXE):
	$(CXX) -g -Wall -o $@ $(SOURCES) -lsfml-graphics -lsfml-window -lsfml-system -lBox2D -std=c++11

.PHONY: $(EXE)

clean:
	rm $(EXE)
