# WARNING: I don't really know what I'm doing here. This is my first Makefile, so it might be a dumpster fire.
INCLUDE_DIR=deps/murmurhash
LIB_DIR=deps/murmurhash
OBJ_DIR=obj
VPATH=$(LIB_DIR)

CC=clang
CFLAGS=-std=c17 -I $(INCLUDE_DIR) -I $(LIB_DIR)

DEPS=$(patsubst %,$(INCLUDE_DIR)/%,$(*.h))
DEPS_LIB=$(patsubst %,$(LIB_DIR)/%,$(*.c))

_OBJ=bloom.o murmurhash.o main.o
OBJ=$(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

$(OBJ_DIR)/%.o: %.c %.h $(DEPS_LIB) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR)/%.o: %.c $(DEPS_LIB) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bloom: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean run
clean:
	rm -f $(OBJ_DIR)/*.o

run: bloom
	./bloom