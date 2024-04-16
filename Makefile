SRC := $(wildcard src/*.c) $(wildcard src/query/*.c) $(wildcard src/range/*.c)
SRC += tree-sitter/lib/src/lib.c
OBJ := $(SRC:.c=.o)

INC :=
LTS_INC := -Iinclude -Itree-sitter/lib/include
TS_INC := -Itree-sitter/lib/include -Itree-sitter/lib/src

CFLAGS := -O3 -fPIC -flto=auto
LTS_CFLAGS := -std=c99 -pedantic -Wall -Wextra -Werror -fvisibility=hidden
TS_CFLAGS := -std=gnu99 -fvisibility=hidden

LDFLAGS :=
POSIX_LDFLAGS := -shared -ldl

lua_tree_sitter.so: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(POSIX_LDFLAGS)

lua_tree_sitter.dll: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $(CFLAGS) $(LTS_CFLAGS) $(INC) $(LTS_INC) $<

tree-sitter/%.o: tree-sitter/%.c
	$(CC) -c -o $@ $(CFLAGS) $(TS_CFLAGS) $(TS_INC) $<

clean:
	$(RM) $(OBJ) lua_tree_sitter.so lua_tree_sitter.dll

.PHONY: clean
