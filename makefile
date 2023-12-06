
INCLUDE_PATH = -Iinclude
LIBS = -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system

bin/juego : src/main.cpp include/*
	g++ $< -o $@  $(INCLUDE_PATH) $(LIBS)


run : bin/juego
	./bin/juego 