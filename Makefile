# WARNING: I don't really know what I'm doing here. This is my first Makefile, so it might be a dumpster fire.
INCLUDE_DIR=include
LIB_DIR=lib
OBJ_DIR=obj
VPATH=$(LIB_DIR):$(INCLUDE_DIR)

CC=clang
CFLAGS=-std=c17 -I $(INCLUDE_DIR) -I $(LIB_DIR)

DEPS=$(patsubst %,$(INCLUDE_DIR)/%,$(*.h))
DEPS_LIB=$(patsubst %,$(LIB_DIR)/%,$(*.c))

_OBJ=bloom.o murmurhash.o tap.o
OBJ=$(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

$(OBJ_DIR)/%.o: %.c %.h $(DEPS_LIB) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR)/main.o: main.c
	$(CC) -c -o $(OBJ_DIR)/main.o main.c $(CFLAGS)

$(OBJ_DIR)/test.o: test.c
	$(CC) -c -o $(OBJ_DIR)/test.o test.c $(CFLAGS)

$(OBJ_DIR)/bench.o: bench.c
	$(CC) -c -o $(OBJ_DIR)/bench.o bench.c $(CFLAGS)

main: $(OBJ) $(OBJ_DIR)/main.o
	$(CC) -o $@ $^ $(CFLAGS)

test_: $(OBJ) $(OBJ_DIR)/test.o
	$(CC) -o $@ $^ $(CFLAGS)

bench_: $(OBJ) $(OBJ_DIR)/bench.o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean run test bench
clean:
	rm -f $(OBJ_DIR)/*.o main test_ bench_

run: main
	./main

test: test_
	./test_

bench: bench_
	time ./bench_