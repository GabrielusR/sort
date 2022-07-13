CFLAGS=-Wall -g
ANSI=-std=c90 -pedantic
BIN=sort
SRC=sort.c

build: $(SRC)
	gcc $(CFLAGS) $(SRC) -o $(BIN)

ansi: $(SRC)
	gcc $(CFLAGS) $(ANSI) $(SRC) -o $(BIN)

clean: $(SRC)
	rm -rf $(BIN)

rebuild: clean build

rebuild_ansi: clean ansi
