#include "node.h"

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include "tree.h"
#include "util.h"

void LTS_push_node(lua_State *L, TSNode target, int parent_idx) {
	LTS_Node *ud = lua_newuserdata(L, sizeof *ud);
	ud->node = target;
	lua_pushvalue(L, parent_idx);
	ud->parent_ref = luaL_ref(L, LUA_REGISTRYINDEX);
	LTS_util_set_metatable(L, LTS_NODE_METATABLE_NAME);
}

LTS_Node LTS_check_lts_node(lua_State *L, int idx) {
	return *(LTS_Node *) luaL_checkudata(L, idx, LTS_NODE_METATABLE_NAME);
}

TSNode LTS_check_node(lua_State *L, int idx) {
	return LTS_check_lts_node(L, idx).node;
}

static int LTS_node_delete(lua_State *L) {
	LTS_Node self = LTS_check_lts_node(L, 1);
	
	luaL_unref(L, LUA_REGISTRYINDEX, self.parent_ref);
	return 0;
}

static int LTS_node_tree(lua_State *L) {
	TSNode self = LTS_check_node(L, 1);

	LTS_push_tree(L, (TSTree *) self.tree);
	return 1;
}

static int LTS_node_eq(lua_State *L) {
	TSNode self = LTS_check_node(L, 1);
	TSNode other = LTS_check_node(L, 2);

	lua_pushboolean(L, ts_node_eq(self, other));
	return 1;
}

static int LTS_node_string(lua_State *L) {
	TSNode self = LTS_check_node(L, 1);

	char *str = ts_node_string(self);
	lua_pushstring(L, str);
	free(str);
	return 1;
}

static const luaL_Reg methods[] = {
	{ "tree", LTS_node_tree },
	{ NULL, NULL }
};

static const luaL_Reg metamethods[] = {
	{ "__eq", LTS_node_eq },
	{ "__tostring", LTS_node_string },
	{ "__gc", LTS_node_delete },
	{ NULL, NULL }
};

static const luaL_Reg funcs[] = {
	{ NULL, NULL }
};

void LTS_make_metatable_node(lua_State *L) {
	LTS_util_make_metatable(L, LTS_NODE_METATABLE_NAME, methods, metamethods);
}

void LTS_make_functable_node(lua_State *L) {
	LTS_util_make_functable(L, LTS_NODE_FUNCTABLE_NAME, funcs);
}
