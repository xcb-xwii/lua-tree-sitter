#include "tree.h"

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include <stdint.h>

#include "language.h"
#include "node.h"
#include "point.h"
#include "range.h"
#include "range_array.h"
#include "util.h"

void LTS_push_tree(lua_State *L, TSTree *target) {
	TSTree **ud = lua_newuserdata(L, sizeof *ud);
	*ud = target;
	LTS_util_set_metatable(L, LTS_TREE_METATABLE_NAME);
}

TSTree **LTS_check_tree(lua_State *L, int idx) {
	return luaL_checkudata(L, idx, LTS_TREE_METATABLE_NAME);
}

static int LTS_tree_delete(lua_State *L) {
	TSTree *self = *LTS_log_gc(LTS_check_tree(L, 1), LTS_TREE_METATABLE_NAME);

	ts_tree_delete(self);
	return 0;
}

static int LTS_tree_copy(lua_State *L) {
	TSTree *self = *LTS_check_tree(L, 1);

	LTS_push_tree(L, ts_tree_copy(self));
	return 1;
}

static int LTS_tree_root_node(lua_State *L) {
	TSTree *self = *LTS_check_tree(L, 1);

	LTS_push_node(L, ts_tree_root_node(self), 1);
	return 1;
}

static int LTS_tree_language(lua_State *L) {
	TSTree *self = *LTS_check_tree(L, 1);

	LTS_push_language(L, (TSLanguage *) ts_tree_language(self));
	return 1;
}

static int LTS_tree_included_ranges(lua_State *L) {
	TSTree *self = *LTS_check_tree(L, 1);

	uint32_t len;
	TSRange *ranges = ts_tree_included_ranges(self, &len);
	LTS_push_range_array(L, (LTS_RangeArray) {
		.ptr = ranges,
		.elem_count = len,
	});
	return 1;
}

static int LTS_tree_edit(lua_State *L) {
	TSTree *self = *LTS_check_tree(L, 1);
	TSInputEdit edit = {
		.start_byte = luaL_checkinteger(L, 2),
		.old_end_byte = luaL_checkinteger(L, 3),
		.new_end_byte = luaL_checkinteger(L, 4),
		.start_point = *LTS_check_point(L, 5),
		.old_end_point = *LTS_check_point(L, 6),
		.new_end_point = *LTS_check_point(L, 7)
	};

	ts_tree_edit(self, &edit);
	return 0;
}

static int LTS_tree_get_changed_ranges(lua_State *L) {
	TSTree *old_tree = *LTS_check_tree(L, 1);
	TSTree *new_tree = *LTS_check_tree(L, 2);

	uint32_t len;
	TSRange *ranges = ts_tree_get_changed_ranges(old_tree, new_tree, &len);
	LTS_push_range_array(L, (LTS_RangeArray) {
		.ptr = ranges,
		.elem_count = len,
	});
	return 1;
}

static const luaL_Reg methods[] = {
	{ "copy", LTS_tree_copy },
	{ "root_node", LTS_tree_root_node },
	//{ "root_node_with_offset", LTS_tree_root_node_with_offset },
	{ "language", LTS_tree_language },
	{ "included_ranges", LTS_tree_included_ranges },
	{ "edit", LTS_tree_edit },
	//{ "print_dot_graph", LTS_tree_print_dot_graph },
	{ NULL, NULL }
};

static const luaL_Reg metamethods[] = {
	{ "__gc", LTS_tree_delete },
	{ NULL, NULL }
};

static const luaL_Reg funcs[] = {
	{ "get_changed_ranges", LTS_tree_get_changed_ranges },
	{ NULL, NULL }
};

void LTS_setup_tree(lua_State *L) {
	LTS_util_make_metatable(L, LTS_TREE_METATABLE_NAME, methods, metamethods);
	LTS_util_make_functable(L, LTS_TREE_FUNCTABLE_NAME, funcs);
}
