#include "language.h"

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include <stdio.h>
#include <stdlib.h>

#include <dlfcn.h>

#include "util.h"

void LTS_push_language(lua_State *L, TSLanguage *target) {
	TSLanguage **ud = lua_newuserdata(L, sizeof *ud);
	*ud = target;
	LTS_util_set_metatable(L, LTS_LANGUAGE_METATABLE_NAME);
}

TSLanguage **LTS_check_language(lua_State *L, int idx) {
	return luaL_checkudata(L, idx, LTS_LANGUAGE_METATABLE_NAME);
}

static int LTS_language_new(lua_State *L) {
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

	LTS_push_language(L, lang_func());	
	return 1;
}

static int LTS_language_version(lua_State *L) {
	TSLanguage *self = *LTS_check_language(L, 1);

	lua_pushinteger(L, ts_language_version(self));
	return 1;
}

static int LTS_language_eq(lua_State *L) {
	TSLanguage *self = *LTS_check_language(L, 1);
	TSLanguage *other = *LTS_check_language(L, 2);

	lua_pushboolean(L, self == other);
	return 1;
}

static const luaL_Reg methods[] = {
	{ "version", LTS_language_version },
	{ NULL, NULL }
};

static const luaL_Reg metamethods[] = {
	{ "__eq", LTS_language_eq },
	{ NULL, NULL }
};

static const luaL_Reg funcs[] = {
	{ "new", LTS_language_new },
	{ NULL, NULL }
};

void LTS_setup_language(lua_State *L) {
	LTS_util_make_metatable(L, LTS_LANGUAGE_METATABLE_NAME, methods, metamethods);
	LTS_util_make_functable(L, LTS_LANGUAGE_FUNCTABLE_NAME, funcs);
}
