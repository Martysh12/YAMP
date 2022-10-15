CC = gcc

LDFLAGS = -lopenmpt -lpulse-simple -largp -lncurses
CXXFLAGS = -Wall -Wextra -Iinclude/

all: bin/yamp

bin/yamp: obj/main.o obj/args.o obj/ui.o
	$(CC) $^ -o $@ $(LDFLAGS) $(CXXFLAGS)

obj/ui.o: src/ui.c include/ui.h
	$(CC) $< -c -o $@ $(CXXFLAGS)

obj/args.o: src/args.c include/args.h
	$(CC) $< -c -o $@ $(CXXFLAGS)

obj/main.o: src/main.c
	$(CC) $< -c -o $@ $(CXXFLAGS)

