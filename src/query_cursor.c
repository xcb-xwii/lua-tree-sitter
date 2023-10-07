#include "query_cursor.h"

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include <stdint.h>

#include "node.h"
#include "point.h"
#include "query.h"
#include "query_match.h"
#include "tree.h"
#include "util.h"

void LTS_push_query_cursor(
	lua_State *L,
	TSQueryCursor *target,
	int query_idx,
	int node_idx
) {
	LTS_QueryCursor *ud = lua_newuserdata(L, sizeof *ud);
	ud->query_cursor = target;

	ud->query = *(TSQuery **) lua_touserdata(L, query_idx);
	lua_pushvalue(L, query_idx);
	ud->query_ref = luaL_ref(L, LUA_REGISTRYINDEX);

	ud->node = lua_touserdata(L, node_idx);
	lua_pushvalue(L, node_idx);
	ud->node_ref = luaL_ref(L, LUA_REGISTRYINDEX);

	LTS_util_set_metatable(L, LTS_QUERY_CURSOR_METATABLE_NAME);
}

LTS_QueryCursor *LTS_check_lts_query_cursor(lua_State *L, int idx) {
	return luaL_checkudata(L, idx, LTS_QUERY_CURSOR_METATABLE_NAME);
}

TSQueryCursor **LTS_check_query_cursor(lua_State *L, int idx) {
	return &LTS_check_lts_query_cursor(L, idx)->query_cursor;
}

static int LTS_query_cursor_new(lua_State *L) {
	TSQueryCursor *self = ts_query_cursor_new();
	TSQuery *query = *LTS_check_query(L, 1);
	LTS_Node node = *LTS_check_lts_node(L, 2);
	
	ts_query_cursor_exec(self, query, node.node);

	LTS_push_query_cursor(L, self, 1, 2);
	return 1;
}

static int LTS_query_cursor_delete(lua_State *L) {
	LTS_QueryCursor self = *LTS_log_gc(LTS_check_lts_query_cursor(L, 1), LTS_QUERY_CURSOR_METATABLE_NAME);
	
	ts_query_cursor_delete(self.query_cursor);
	luaL_unref(L, LUA_REGISTRYINDEX, self.query_ref);
	luaL_unref(L, LUA_REGISTRYINDEX, self.node_ref);
	return 0;
}

static int LTS_query_cursor_query(lua_State *L) {
	LTS_QueryCursor self = *LTS_check_lts_query_cursor(L, 1);

	lua_rawgeti(L, LUA_REGISTRYINDEX, self.query_ref);
	return 1;
}

static int LTS_query_cursor_set_point_range(lua_State *L) {
	TSQueryCursor *self = *LTS_check_query_cursor(L, 1);
	TSPoint start = *LTS_check_point(L, 2);
	TSPoint end = *LTS_check_point(L, 3);

	ts_query_cursor_set_point_range(self, start, end);
	return 0;
}

static int LTS_query_cursor_next_match(lua_State *L) {
	TSQueryCursor *self = *LTS_check_query_cursor(L, 1);

	TSQueryMatch match;
	bool ok = ts_query_cursor_next_match(self, &match);

	if (ok) {
		LTS_push_query_match(L, match, 1);
		return 1;
	}

	lua_pushnil(L);
	return 1;
}

static int LTS_query_cursor_next_capture(lua_State *L) {
	TSQueryCursor *self = *LTS_check_query_cursor(L, 1);

	TSQueryMatch match;
	uint32_t capture_index;
	bool ok = ts_query_cursor_next_capture(self, &match, &capture_index);

	if (ok) {
		LTS_push_query_match(L, match, 1);
		lua_pushinteger(L, capture_index);
		return 2;
	}

	lua_pushnil(L);
	return 1;
}

static const luaL_Reg methods[] = {
	{ "query", LTS_query_cursor_query },
	//{ "did_exceed_match_limit", LTS_query_cursor_did_exceed_match_limit },
	//{ "match_limit", lts_query_cursor_match_limit },
	//{ "set_match_limit", lts_query_cursor_set_match_limit },
	//{ "set_byte_range", LTS_query_cursor_set_byte_range },
	{ "set_point_range", LTS_query_cursor_set_point_range },
	{ "next_match", LTS_query_cursor_next_match },
	// { "remove_match", LTS_query_cursor_remove_match },
	{ "next_capture", LTS_query_cursor_next_capture },
	//{ "set_max_start_depth", LTS_query_cursor_set_max_start_depth },
	{ NULL, NULL }
};

static const luaL_Reg metamethods[] = {
	{ "__gc", LTS_query_cursor_delete },
	{ NULL, NULL }
};

static const luaL_Reg funcs[] = {
	{ "new", LTS_query_cursor_new },
	{ NULL, NULL }
};

void LTS_make_metatable_query_cursor(lua_State *L) {
	LTS_util_make_metatable(L, LTS_QUERY_CURSOR_METATABLE_NAME, methods, metamethods);
}

void LTS_make_functable_query_cursor(lua_State *L) {
	LTS_util_make_functable(L, LTS_QUERY_CURSOR_FUNCTABLE_NAME, funcs);
}
