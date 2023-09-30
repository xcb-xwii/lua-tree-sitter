#include "array.h"

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include <string.h>

#include "util.h"

void LTS_push_array(lua_State *L, LTS_Array target) {
	LTS_Array *ud = lua_newuserdata(L, sizeof *ud);
	*ud = target;
	LTS_util_set_metatable(L, LTS_ARRAY_METATABLE_NAME);
}

LTS_Array LTS_check_array(lua_State *L, int idx) {
	return *(LTS_Array *) luaL_checkudata(L, idx, LTS_ARRAY_METATABLE_NAME);
}

static int LTS_array_delete(lua_State *L) {
	LTS_Array self = LTS_check_array(L, 1);

	if (self.managed) free(self.ptr);
	return 0;
}

static int LTS_array_len(lua_State *L) {
	LTS_Array self = LTS_check_array(L, 1);

	lua_pushinteger(L, self.elem_count);
	return 1;
}

static int LTS_array_index(lua_State *L) {
	LTS_Array self = LTS_check_array(L, 1);
	lua_Integer idx = luaL_checkinteger(L, 2);

	luaL_argcheck(L,
		idx > 0,
		2,
		"attempt to index "LTS_ARRAY_METATABLE_NAME" with non-positive index"
	);
	luaL_argcheck(L,
		idx <= self.elem_count,
		2,
		"attempt to index "LTS_ARRAY_METATABLE_NAME" beyond last element"
	);

	void *ud = lua_newuserdata(L, self.elem_size);
	memcpy(ud, self.ptr + ((idx - 1) * self.elem_size), self.elem_size);
	LTS_util_set_metatable(L, self.mt_name);
	return 1;
}

static int LTS_array_newindex(lua_State *L) {
	LTS_Array self = LTS_check_array(L, 1);
	lua_Integer idx = luaL_checkinteger(L, 2);
	void *ud = luaL_checkudata(L, 3, self.mt_name);

	luaL_argcheck(L,
		self.managed,
		1,
		"attempt to mutate unmanaged "LTS_ARRAY_METATABLE_NAME
	);
	luaL_argcheck(L,
		idx > 0,
		2,
		"attempt to index "LTS_ARRAY_METATABLE_NAME" with non-positive index"
	);
	luaL_argcheck(L,
		idx <= self.elem_count,
		2,
		"attempt to index "LTS_ARRAY_METATABLE_NAME" beyond last element"
	);

	memcpy(self.ptr + ((idx - 1) * self.elem_size), ud, self.elem_size);
	return 0;
}

static const luaL_Reg metamethods[] = {
	{ "__len", LTS_array_len },
	{ "__index", LTS_array_index },
	{ "__newindex", LTS_array_newindex },
	{ "__gc", LTS_array_delete },
	{ NULL, NULL }
};

void LTS_make_metatable_array(lua_State *L) {
	LTS_util_make_metatable(L, LTS_ARRAY_METATABLE_NAME, NULL, metamethods);
}

void LTS_make_functable_array(lua_State *L) {
	LTS_util_make_functable(L, LTS_ARRAY_FUNCTABLE_NAME, NULL);
}
