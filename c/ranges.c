#include "ranges.h"

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include "range.h"
#include "util.h"

void LTS_push_ranges(lua_State *L, LTS_Ranges target) {
	LTS_Ranges *ud = lua_newuserdata(L, sizeof *ud);
	*ud = target;
	LTS_util_set_metatable(L, LTS_RANGES_METATABLE_NAME);
}

LTS_Ranges LTS_check_ranges(lua_State *L, int idx) {
	return *(LTS_Ranges *) luaL_checkudata(L, idx, LTS_RANGES_METATABLE_NAME);
}

static int LTS_ranges_delete(lua_State *L) {
	LTS_Ranges self = LTS_check_ranges(L, 1);

	if (self.managed) free(self.ptr);
	return 0;
}

static int LTS_ranges_len(lua_State *L) {
	LTS_Ranges self = LTS_check_ranges(L, 1);

	lua_pushinteger(L, self.elem_count);
	return 1;
}

static int LTS_ranges_index(lua_State *L) {
	LTS_Ranges self = LTS_check_ranges(L, 1);
	lua_Integer idx = luaL_checkinteger(L, 2);

	luaL_argcheck(L,
		idx > 0,
		2,
		"attempt to index "LTS_RANGES_METATABLE_NAME" with non-positive index"
	);
	luaL_argcheck(L,
		idx <= self.elem_count,
		2,
		"attempt to index "LTS_RANGES_METATABLE_NAME" beyond last element"
	);

	LTS_push_range(L, self.ptr[idx - 1]);
	return 1;
}

static int LTS_ranges_newindex(lua_State *L) {
	LTS_Ranges self = LTS_check_ranges(L, 1);
	lua_Integer idx = luaL_checkinteger(L, 2);
	TSRange range = LTS_check_range(L, 3);

	luaL_argcheck(L,
		self.managed,
		1,
		"attempt to mutate unmanaged "LTS_RANGES_METATABLE_NAME
	);
	luaL_argcheck(L,
		idx > 0,
		2,
		"attempt to index "LTS_RANGES_METATABLE_NAME" with non-positive index"
	);
	luaL_argcheck(L,
		idx <= self.elem_count,
		2,
		"attempt to index "LTS_RANGES_METATABLE_NAME" beyond last element"
	);

	self.ptr[idx - 1] = range;
	return 0;
}

static const luaL_Reg metamethods[] = {
	{ "__len", LTS_ranges_len },
	{ "__index", LTS_ranges_index },
	{ "__newindex", LTS_ranges_newindex },
	{ "__gc", LTS_ranges_delete },
	{ NULL, NULL }
};

void LTS_make_metatable_ranges(lua_State *L) {
	LTS_util_make_metatable(L, LTS_RANGES_METATABLE_NAME, NULL, metamethods);
}

void LTS_make_functable_ranges(lua_State *L) {
	LTS_util_make_functable(L, LTS_RANGES_FUNCTABLE_NAME, NULL);
}
