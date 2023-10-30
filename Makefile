SRC := $(wildcard src/*.c) $(wildcard src/query/*.c) $(wildcard src/range/*.c)
SRC += tree-sitter/lib/src/lib.c
OBJ := $(SRC:.c=.o)

INC := -Iinclude -Itree-sitter/lib/include
LUA_INC :=
TS_INC := -Itree-sitter/lib/include -Itree-sitter/lib/src

CFLAGS := -O2 -Wall -Wextra -Werror -std=c99 -pedantic -fPIC
TS_CFLAGS := -O2 -Wall -Wextra -Werror -std=gnu99 -fPIC

LIBS :=
POSIX_LIBS := -ldl

lua_tree_sitter.so: $(OBJ)
	$(CC) -shared -o $@ $^ $(LIBS) $(POSIX_LIBS)

lua_tree_sitter.dll: $(OBJ)
	$(CC) -shared -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) -c -o $@ $(CFLAGS) $(LUA_INC) $(INC) $<

tree-sitter/%.o: tree-sitter/%.c
	$(CC) -c -o $@ $(TS_CFLAGS) $(TS_INC) $<

clean:
	$(RM) $(OBJ) lua_tree_sitter.so lua_tree_sitter.dll

.PHONY: clean
