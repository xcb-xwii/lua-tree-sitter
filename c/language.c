#include "language.h"

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include "util.h"

void LTS_push_language(lua_State *L, TSLanguage *target) {
	TSLanguage **ud = lua_newuserdata(L, sizeof *ud);
	*ud = target;
	LTS_util_set_metatable(L, LTS_LANGUAGE_METATABLE_NAME);
}

TSLanguage *LTS_check_language(lua_State *L, int idx) {
	return *(TSLanguage **) luaL_checkudata(L, idx, LTS_LANGUAGE_METATABLE_NAME);
}

static int LTS_language_version(lua_State *L) {
	TSLanguage *self = LTS_check_language(L, 1);

	lua_pushinteger(L, ts_language_version(self));
	return 1;
}

static int LTS_language_eq(lua_State *L) {
	TSLanguage *self = LTS_check_language(L, 1);
	TSLanguage *other = LTS_check_language(L, 2);

	lua_pushboolean(L, self == other);
	return 1;
}

static const luaL_Reg metamethods[] = {
	{ "__eq", LTS_language_eq },
	{ NULL, NULL }
};

static const luaL_Reg funcs[] = {
	{ "version", LTS_language_version },
	{ NULL, NULL }
};

void LTS_make_metatable_language(lua_State *L) {
	LTS_util_make_metatable(L, LTS_LANGUAGE_METATABLE_NAME, NULL, metamethods);
}

void LTS_make_functable_language(lua_State *L) {
	LTS_util_make_functable(L, LTS_LANGUAGE_FUNCTABLE_NAME, funcs);
}
