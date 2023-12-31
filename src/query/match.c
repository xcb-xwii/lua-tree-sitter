#include <lts/query/match.h>

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include <lts/query/init.h>
#include <lts/query/capture.h>
#include <lts/util.h>

void LTS_push_query_match(lua_State *L, TSQueryMatch target, int cursor_idx) {
	LTS_QueryMatch *ud = lua_newuserdata(L, sizeof *ud);
	ud->match = target;

	ud->cursor = lua_touserdata(L, cursor_idx);
	lua_pushvalue(L, cursor_idx);
	ud->cursor_ref = luaL_ref(L, LUA_REGISTRYINDEX);

	LTS_util_set_metatable(L, LTS_QUERY_MATCH_METATABLE_NAME);
}

LTS_QueryMatch *LTS_check_lts_query_match(lua_State *L, int idx) {
	return luaL_checkudata(L, idx, LTS_QUERY_MATCH_METATABLE_NAME);
}

TSQueryMatch *LTS_check_query_match(lua_State *L, int idx) {
	return &LTS_check_lts_query_match(L, idx)->match;
}

static int LTS_query_match_delete(lua_State *L) {
	LTS_QueryMatch self = *LTS_log_gc(LTS_check_lts_query_match(L, 1), LTS_QUERY_MATCH_METATABLE_NAME);
	
	luaL_unref(L, LUA_REGISTRYINDEX, self.cursor_ref);
	return 0;
}

static int LTS_query_match_pattern_index(lua_State *L) {
	TSQueryMatch self = *LTS_check_query_match(L, 1);
	
	lua_pushinteger(L, self.pattern_index);
	return 1;
}

static int LTS_query_match_capture_count(lua_State *L) {
	TSQueryMatch self = *LTS_check_query_match(L, 1);
	
	lua_pushinteger(L, self.capture_count);
	return 1;
}

static int LTS_query_match_capture_at(lua_State *L) {
	TSQueryMatch self = *LTS_check_query_match(L, 1);
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

static int LTS_query_match_query(lua_State *L) {
	LTS_QueryMatch self = *LTS_check_lts_query_match(L, 1);

	lua_rawgeti(L, LUA_REGISTRYINDEX, self.cursor->query_ref);
	return 1;
}

static int LTS_query_match_captures_to_table(lua_State *L) {
	LTS_QueryMatch self = *LTS_check_lts_query_match(L, 1);

	TSQueryMatch match = self.match;
	lua_settop(L, 1);
	lua_createtable(L, self.match.capture_count, 0);
	for (uint16_t i = 0; i < self.match.capture_count; i++) {
		LTS_push_query_capture(L, match.captures[i], 1);
		lua_rawseti(L, -2, i + 1);
	}
	return 1;
}

static const luaL_Reg methods[] = {
	{ "pattern_index", LTS_query_match_pattern_index },
	{ "capture_count", LTS_query_match_capture_count },
	{ "capture_at", LTS_query_match_capture_at },
	{ "captures_to_table", LTS_query_match_captures_to_table },
	{ "query", LTS_query_match_query },
	{ NULL, NULL }
};

static const luaL_Reg metamethods[] = {
	{ "__gc", LTS_query_match_delete },
	{ NULL, NULL }
};

void LTS_setup_query_match(lua_State *L) {
	LTS_util_make_metatable(L, LTS_QUERY_MATCH_METATABLE_NAME, methods, metamethods);
}
