#include "query_capture.h"

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include "query_cursor.h"
#include "query_match.h"
#include "node.h"
#include "util.h"

void LTS_push_query_capture(lua_State *L, TSQueryCapture target, int match_idx) {
	LTS_QueryCapture *ud = lua_newuserdata(L, sizeof *ud);
	ud->capture = target;
	lua_pushvalue(L, match_idx);
	ud->match_ref = luaL_ref(L, LUA_REGISTRYINDEX);
	LTS_util_set_metatable(L, LTS_QUERY_CAPTURE_METATABLE_NAME);
}

LTS_QueryCapture LTS_check_lts_query_capture(lua_State *L, int idx) {
	return *(LTS_QueryCapture *) luaL_checkudata(L, idx, LTS_QUERY_CAPTURE_METATABLE_NAME);
}

TSQueryCapture LTS_check_query_capture(lua_State *L, int idx) {
	return LTS_check_lts_query_capture(L, idx).capture;
}

static int LTS_query_capture_delete(lua_State *L) {
	LTS_QueryCapture self = LTS_check_lts_query_capture(L, 1);
	
	luaL_unref(L, LUA_REGISTRYINDEX, self.match_ref);
	return 0;
}

static int LTS_query_capture_node(lua_State *L) {
	LTS_QueryCapture self = LTS_check_lts_query_capture(L, 1);

	lua_rawgeti(L, LUA_REGISTRYINDEX, self.match_ref);
	LTS_QueryMatch *match = lua_touserdata(L, -1);
	lua_rawgeti(L, LUA_REGISTRYINDEX, match->cursor_ref);
	LTS_QueryCursor *cursor = lua_touserdata(L, -1);
	lua_rawgeti(L, LUA_REGISTRYINDEX, cursor->node_ref);
	LTS_Node *origin = lua_touserdata(L, -1);
	lua_rawgeti(L, LUA_REGISTRYINDEX, origin->tree_ref);

	LTS_push_node(L, self.capture.node, -1);
	return 1;
}

static int LTS_query_capture_index(lua_State *L) {
	TSQueryCapture self = LTS_check_query_capture(L, 1);
	
	lua_pushinteger(L, self.index);
	return 1;
}

static const luaL_Reg methods[] = {
	{ "node", LTS_query_capture_node },
	{ "index", LTS_query_capture_index },
	{ NULL, NULL }
};

static const luaL_Reg metamethods[] = {
	{ "__gc", LTS_query_capture_delete },
	{ NULL, NULL }
};

void LTS_make_metatable_query_capture(lua_State *L) {
	LTS_util_make_metatable(L, LTS_QUERY_CAPTURE_METATABLE_NAME, methods, metamethods);
}

void LTS_make_functable_query_capture(lua_State *L) {
	LTS_util_make_functable(L, LTS_QUERY_CAPTURE_FUNCTABLE_NAME, NULL);
}