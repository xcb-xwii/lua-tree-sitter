#include <lts/node.h>

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include <stdint.h>

#include <lts/point.h>
#include <lts/tree.h>
#include <lts/util.h>

void LTS_push_node(lua_State *L, TSNode target, int tree_idx) {
	if (ts_node_is_null(target)) {
		lua_pushnil(L);
		return;
	}

	LTS_Node *ud = lua_newuserdata(L, sizeof *ud);
	ud->node = target;
	lua_pushvalue(L, tree_idx);
	ud->tree_ref = luaL_ref(L, LUA_REGISTRYINDEX);
	LTS_util_set_metatable(L, LTS_NODE_METATABLE_NAME);
}

LTS_Node *LTS_check_lts_node(lua_State *L, int idx) {
	return luaL_checkudata(L, idx, LTS_NODE_METATABLE_NAME);
}

TSNode *LTS_check_node(lua_State *L, int idx) {
	return &LTS_check_lts_node(L, idx)->node;
}

static int LTS_node_delete(lua_State *L) {
	LTS_Node self = *LTS_log_gc(LTS_check_lts_node(L, 1), LTS_NODE_METATABLE_NAME);
	
	luaL_unref(L, LUA_REGISTRYINDEX, self.tree_ref);
	return 0;
}

static int LTS_node_tree(lua_State *L) {
	LTS_Node self = *LTS_check_lts_node(L, 1);

	lua_rawgeti(L, LUA_REGISTRYINDEX, self.tree_ref);
	return 1;
}

static int LTS_node_type(lua_State *L) {
	TSNode self = *LTS_check_node(L, 1);

	lua_pushstring(L, ts_node_type(self));
	return 1;
}

static int LTS_node_start_byte(lua_State *L) {
	TSNode self = *LTS_check_node(L, 1);

	lua_pushinteger(L, ts_node_start_byte(self));
	return 1;
}

static int LTS_node_start_point(lua_State *L) {
	TSNode self = *LTS_check_node(L, 1);

	LTS_push_point(L, ts_node_start_point(self));
	return 1;
}

static int LTS_node_end_byte(lua_State *L) {
	TSNode self = *LTS_check_node(L, 1);

	lua_pushinteger(L, ts_node_end_byte(self));
	return 1;
}

static int LTS_node_end_point(lua_State *L) {
	TSNode self = *LTS_check_node(L, 1);

	LTS_push_point(L, ts_node_end_point(self));
	return 1;
}

static int LTS_node_eq(lua_State *L) {
	TSNode self = *LTS_check_node(L, 1);
	TSNode other = *LTS_check_node(L, 2);

	lua_pushboolean(L, ts_node_eq(self, other));
	return 1;
}

static int LTS_node_string(lua_State *L) {
	TSNode self = *LTS_check_node(L, 1);

	char *str = ts_node_string(self);
	lua_pushstring(L, str);
	free(str);
	return 1;
}

#define SIMPLE_BOOL_GETTER(prop) \
	static int LTS_node_##prop(lua_State *L) { \
		TSNode self = *LTS_check_node(L, 1); \
		\
		lua_pushboolean(L, ts_node_##prop(self)); \
		return 1; \
	}

SIMPLE_BOOL_GETTER(is_named)
SIMPLE_BOOL_GETTER(is_missing)
SIMPLE_BOOL_GETTER(is_extra)
SIMPLE_BOOL_GETTER(has_changes)
SIMPLE_BOOL_GETTER(has_error)

#undef SIMPLE_BOOL_GETTER

#define SIMPLE_NODE_GETTER(kind) \
	static int LTS_node_##kind(lua_State *L) { \
		LTS_Node self = *LTS_check_lts_node(L, 1); \
		\
		lua_settop(L, 0); \
		lua_rawgeti(L, LUA_REGISTRYINDEX, self.tree_ref); \
		LTS_push_node(L, ts_node_##kind(self.node), 1); \
		return 1; \
	}

SIMPLE_NODE_GETTER(parent)

static int LTS_node_child(lua_State *L) {
	LTS_Node self = *LTS_check_lts_node(L, 1);
	uint32_t index = luaL_checkinteger(L, 2);

	lua_settop(L, 0);
	lua_rawgeti(L, LUA_REGISTRYINDEX, self.tree_ref);
	LTS_push_node(L, ts_node_child(self.node, index), 1);
	return 1;
}

static int LTS_node_field_name_for_child(lua_State *L) {
	TSNode self = *LTS_check_node(L, 1);
	uint32_t index = luaL_checkinteger(L, 2);

	const char *name = ts_node_field_name_for_child(self, index);
	if (name) {
		lua_pushstring(L, name);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

static int LTS_node_child_count(lua_State *L) {
	TSNode self = *LTS_check_node(L, 1);

	lua_pushinteger(L, ts_node_child_count(self));
	return 1;
}

static int LTS_node_named_child(lua_State *L) {
	LTS_Node self = *LTS_check_lts_node(L, 1);
	uint32_t index = luaL_checkinteger(L, 2);

	lua_settop(L, 0);
	lua_rawgeti(L, LUA_REGISTRYINDEX, self.tree_ref);
	LTS_push_node(L, ts_node_named_child(self.node, index), 1);
	return 1;
}

static int LTS_node_named_child_count(lua_State *L) {
	TSNode self = *LTS_check_node(L, 1);

	lua_pushinteger(L, ts_node_named_child_count(self));
	return 1;
}

static int LTS_node_child_by_field_name(lua_State *L) {
	LTS_Node self = *LTS_check_lts_node(L, 1);
	size_t len;
	const char *name = luaL_checklstring(L, 2, &len);

	lua_settop(L, 0);
	lua_rawgeti(L, LUA_REGISTRYINDEX, self.tree_ref);
	LTS_push_node(L, ts_node_child_by_field_name(self.node, name, len), 1);
	return 1;
}

static int LTS_node_child_by_field_id(lua_State *L) {
	LTS_Node self = *LTS_check_lts_node(L, 1);
	TSFieldId index = luaL_checkinteger(L, 2);

	lua_settop(L, 0);
	lua_rawgeti(L, LUA_REGISTRYINDEX, self.tree_ref);
	LTS_push_node(L, ts_node_child_by_field_id(self.node, index), 1);
	return 1;
}

SIMPLE_NODE_GETTER(next_sibling)
SIMPLE_NODE_GETTER(prev_sibling)
SIMPLE_NODE_GETTER(next_named_sibling)
SIMPLE_NODE_GETTER(prev_named_sibling)

#undef SIMPLE_NODE_GETTER

static int LTS_node_first_child_for_byte(lua_State *L) {
	LTS_Node self = *LTS_check_lts_node(L, 1);
	uint32_t byte = luaL_checkinteger(L, 2);

	lua_settop(L, 0);
	lua_rawgeti(L, LUA_REGISTRYINDEX, self.tree_ref);
	LTS_push_node(L, ts_node_first_child_for_byte(self.node, byte), 1);
	return 1;
}

static int LTS_node_first_named_child_for_byte(lua_State *L) {
	LTS_Node self = *LTS_check_lts_node(L, 1);
	uint32_t byte = luaL_checkinteger(L, 2);

	lua_settop(L, 0);
	lua_rawgeti(L, LUA_REGISTRYINDEX, self.tree_ref);
	LTS_push_node(L, ts_node_first_named_child_for_byte(self.node, byte), 1);
	return 1;
}

static int LTS_node_descendant_for_byte_range(lua_State *L) {
	LTS_Node self = *LTS_check_lts_node(L, 1);
	uint32_t start = luaL_checkinteger(L, 2);
	uint32_t end = luaL_checkinteger(L, 2);

	lua_settop(L, 0);
	lua_rawgeti(L, LUA_REGISTRYINDEX, self.tree_ref);
	LTS_push_node(L, ts_node_descendant_for_byte_range(self.node, start, end), 1);
	return 1;
}

static int LTS_node_descendant_for_point_range(lua_State *L) {
	LTS_Node self = *LTS_check_lts_node(L, 1);
	TSPoint start = *LTS_check_point(L, 2);
	TSPoint end = *LTS_check_point(L, 2);

	lua_settop(L, 0);
	lua_rawgeti(L, LUA_REGISTRYINDEX, self.tree_ref);
	LTS_push_node(L, ts_node_descendant_for_point_range(self.node, start, end), 1);
	return 1;
}

static int LTS_node_named_descendant_for_byte_range(lua_State *L) {
	LTS_Node self = *LTS_check_lts_node(L, 1);
	uint32_t start = luaL_checkinteger(L, 2);
	uint32_t end = luaL_checkinteger(L, 2);

	lua_settop(L, 0);
	lua_rawgeti(L, LUA_REGISTRYINDEX, self.tree_ref);
	LTS_push_node(L, ts_node_named_descendant_for_byte_range(self.node, start, end), 1);
	return 1;
}

static int LTS_node_named_descendant_for_point_range(lua_State *L) {
	LTS_Node self = *LTS_check_lts_node(L, 1);
	TSPoint start = *LTS_check_point(L, 2);
	TSPoint end = *LTS_check_point(L, 2);

	lua_settop(L, 0);
	lua_rawgeti(L, LUA_REGISTRYINDEX, self.tree_ref);
	LTS_push_node(L, ts_node_named_descendant_for_point_range(self.node, start, end), 1);
	return 1;
}

static const luaL_Reg methods[] = {
	{ "tree", LTS_node_tree },
	{ "type", LTS_node_type },
	{ "start_byte", LTS_node_start_byte },
	{ "start_point", LTS_node_start_point },
	{ "end_byte", LTS_node_end_byte },
	{ "end_point", LTS_node_end_point },
	{ "is_named", LTS_node_is_named },
	{ "is_missing", LTS_node_is_missing },
	{ "is_extra", LTS_node_is_extra },
	{ "has_changes", LTS_node_has_changes },
	{ "has_error", LTS_node_has_error },
	{ "parent", LTS_node_parent },
	{ "child", LTS_node_child },
	{ "field_name_for_child", LTS_node_field_name_for_child },
	{ "child_count", LTS_node_child_count },
	{ "named_child", LTS_node_named_child },
	{ "named_child_count", LTS_node_named_child_count },
	{ "child_by_field_name", LTS_node_child_by_field_name },
	{ "child_by_field_id", LTS_node_child_by_field_id },
	{ "next_sibling", LTS_node_next_sibling },
	{ "prev_sibling", LTS_node_prev_sibling },
	{ "next_named_sibling", LTS_node_next_named_sibling },
	{ "prev_named_sibling", LTS_node_prev_named_sibling },
	{ "first_child_for_byte", LTS_node_first_child_for_byte },
	{ "first_named_child_for_byte", LTS_node_first_named_child_for_byte },
	{ "descendant_for_byte_range", LTS_node_descendant_for_byte_range },
	{ "descendant_for_point_range", LTS_node_descendant_for_point_range },
	{ "named_descendant_for_byte_range", LTS_node_named_descendant_for_byte_range },
	{ "named_descendant_for_point_range", LTS_node_named_descendant_for_point_range },
	{ NULL, NULL }
};

static const luaL_Reg metamethods[] = {
	{ "__eq", LTS_node_eq },
	{ "__tostring", LTS_node_string },
	{ "__gc", LTS_node_delete },
	{ NULL, NULL }
};

void LTS_setup_node(lua_State *L) {
	LTS_util_make_metatable(L, LTS_NODE_METATABLE_NAME, methods, metamethods);
}
