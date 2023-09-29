#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include <stdio.h>
#include <stdlib.h>

#include <dlfcn.h>

#include "input.h"
#include "language.h"
#include "node.h"
#include "parser.h"
#include "point.h"
#include "tree.h"
#include "util.h"

static int LTS_load(lua_State *L) {
	const char *path = luaL_checkstring(L, 1);
	const char *lang_name = luaL_checkstring(L, 2);

	void *dl = dlopen(path, RTLD_NOW | RTLD_LOCAL);
	if (!dl) {
		return luaL_error(L, "could not load dynamic library: %s", dlerror());
	}

	size_t sym_len = snprintf(NULL, 0, "tree_sitter_%s", lang_name) + 1;
	char *sym = malloc(sym_len);
	snprintf(sym, sym_len, "tree_sitter_%s", lang_name);

	TSLanguage *(*lang_func)(void) = dlsym(dl, sym);
	free(sym);
	if (!lang_func) {
		dlclose(dl);
		return luaL_error(L,
			"could not load symbol for tree_sitter_%s: %s",
			lang_name, dlerror()
		);
	}

	TSLanguage *lang = lang_func();
	LTS_push_language(L, lang);	

	return 1;
}

static const luaL_Reg reg[] = {
	{"load", LTS_load},
	{NULL, NULL}
};

int luaopen_lua_tree_sitter(lua_State *L) {
	LTS_make_metatable_input(L);
	LTS_make_metatable_language(L);
	LTS_make_metatable_node(L);
	LTS_make_metatable_parser(L);
	LTS_make_metatable_point(L);
	LTS_make_metatable_tree(L);

	lua_createtable(L, 0, 0);
	LTS_util_set_funcs(L, reg);

	LTS_make_functable_input(L);
	LTS_make_functable_language(L);
	LTS_make_functable_node(L);
	LTS_make_functable_parser(L);
	LTS_make_functable_point(L);
	LTS_make_functable_tree(L);

	return 1;
}
