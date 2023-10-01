#include "query_match.h"

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include "query_capture.h"
#include "util.h"

void LTS_push_query_match(lua_State *L, TSQueryMatch target, int cursor_idx) {
	LTS_QueryMatch *ud = lua_newuserdata(L, sizeof *ud);
	ud->match = target;
	lua_pushvalue(L, cursor_idx);
	ud->cursor_ref = luaL_ref(L, LUA_REGISTRYINDEX);
	LTS_util_set_metatable(L, LTS_QUERY_MATCH_METATABLE_NAME);
}

LTS_QueryMatch LTS_check_lts_query_match(lua_State *L, int idx) {
	return *(LTS_QueryMatch *) luaL_checkudata(L, idx, LTS_QUERY_MATCH_METATABLE_NAME);
}

TSQueryMatch LTS_check_query_match(lua_State *L, int idx) {
	return LTS_check_lts_query_match(L, idx).match;
}

static int LTS_query_match_delete(lua_State *L) {
	LTS_QueryMatch self = LTS_check_lts_query_match(L, 1);
	
	luaL_unref(L, LUA_REGISTRYINDEX, self.cursor_ref);
	return 0;
}

static int LTS_query_match_pattern_index(lua_State *L) {
	TSQueryMatch self = LTS_check_query_match(L, 1);
	
	lua_pushinteger(L, self.pattern_index);
	return 1;
}

static int LTS_query_match_capture_count(lua_State *L) {
	TSQueryMatch self = LTS_check_query_match(L, 1);
	
	lua_pushinteger(L, self.capture_count);
	return 1;
}

static int LTS_query_match_capture_at(lua_State *L) {
	TSQueryMatch self = LTS_check_query_match(L, 1);
	lua_Integer idx = luaL_checkinteger(L, 2);

	luaL_argcheck(L,
		idx >= 0,
		2,
		"attempt to index "LTS_QUERY_MATCH_METATABLE_NAME" with negative index"
	);
	luaL_argcheck(L,
		idx < self.capture_count,
		2,
		"attempt to index "LTS_QUERY_MATCH_METATABLE_NAME" beyond last element"
	);

	LTS_push_query_capture(L, self.captures[idx], 1);
	return 1;
}

static const luaL_Reg methods[] = {
	//{ "unpack", LTS_query_match_unpack },
	//{ "to_table", LTS_query_match_to_table },
	{ "pattern_index", LTS_query_match_pattern_index },
	{ "capture_count", LTS_query_match_capture_count },
	{ "capture_at", LTS_query_match_capture_at },
	//{ "captures_to_table", LTS_query_match_captures_to_table },
	{ NULL, NULL }
};

static const luaL_Reg metamethods[] = {
	{ "__gc", LTS_query_match_delete },
	{ NULL, NULL }
};

void LTS_make_metatable_query_match(lua_State *L) {
	LTS_util_make_metatable(L, LTS_QUERY_MATCH_METATABLE_NAME, methods, metamethods);
}

void LTS_make_functable_query_match(lua_State *L) {
	LTS_util_make_functable(L, LTS_QUERY_MATCH_FUNCTABLE_NAME, NULL);
}
