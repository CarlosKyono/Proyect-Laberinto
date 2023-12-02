
INCLUDE_PATH = -Iinclude
LIBS = -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system

bin/juego : src/main.cpp
	g++ $< -o $@  $(INCLUDE_PATH) $(LIBS)


run : bin/juego
	./bin/juego 