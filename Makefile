SRC := $(wildcard src/*.c) $(wildcard src/query/*.c) $(wildcard src/range/*.c)
SRC += tree-sitter/lib/src/lib.c
OBJ := $(SRC:.c=.o)

LUA_INC :=
LTS_INC := -Iinclude -Itree-sitter/lib/include
TS_INC := -Itree-sitter/lib/include -Itree-sitter/lib/src

CFLAGS := -O3 -fvisibility=hidden -fPIC -flto=auto
LTS_CFLAGS := -std=c11 -pedantic -Wall -Wextra -Werror
TS_CFLAGS := -std=c11 -DTREE_SITTER_HIDE_SYMBOLS -DTREE_SITTER_HIDDEN_SYMBOLS -D_POSIX_C_SOURCE=200112L -D_DEFAULT_SOURCE

LDFLAGS := -shared
LUA_LDFLAGS = -llua
POSIX_LDFLAGS := -ldl


lua_tree_sitter.so: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LUA_LDFLAGS) $(POSIX_LDFLAGS)

lua_tree_sitter.dll: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LUA_LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $(CFLAGS) $(LTS_CFLAGS) $(LUA_INC) $(LTS_INC) $<

tree-sitter/%.o: tree-sitter/%.c
	$(CC) -c -o $@ $(CFLAGS) $(TS_CFLAGS) $(TS_INC) $<

clean:
	$(RM) $(OBJ) lua_tree_sitter.so lua_tree_sitter.dll

.PHONY: clean
