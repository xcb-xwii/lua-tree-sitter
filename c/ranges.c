#include "ranges.h"

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include <string.h>

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

	free(self.ptr);
	return 0;
}

static int LTS_ranges_new(lua_State *L) {
	lua_settop(L, 1);
	luaL_checktype(L, 1, LUA_TTABLE);
	size_t elem_count = lua_rawlen(L, 1);

	TSRange *ptr = malloc(elem_count * sizeof *ptr);
	lua_getfield(L, LUA_REGISTRYINDEX, LTS_RANGE_METATABLE_NAME);

	size_t i = 1;
	for (; i <= elem_count; i++) {
		lua_rawgeti(L, 1, i);
		TSRange *elem = lua_touserdata(L, 3);

		if (!elem) goto fail;
		if (!lua_getmetatable(L, 3)) goto fail;
		if (!lua_rawequal(L, 2, 4)) goto fail;

		ptr[i - 1] = *elem;
		lua_pop(L, 2);
	}

	LTS_push_ranges(L, (LTS_Ranges) {
		.ptr = ptr,
		.elem_count = elem_count
	});
	return 1;

fail:
	free(ptr);
	return luaL_error(L,
		"bad element #%d in array ("LTS_RANGE_METATABLE_NAME" expected, got %s)",
		i, luaL_typename(L, 3)
	);
}

static int LTS_ranges_pack(lua_State *L) {
	size_t elem_count = lua_gettop(L);

	TSRange *ptr = malloc(elem_count * sizeof *ptr);
	lua_getfield(L, LUA_REGISTRYINDEX, LTS_RANGE_METATABLE_NAME);

	for (size_t i = 1; i <= elem_count; i++) {
		ptr[i - 1] = LTS_check_range(L, i);
	}

	LTS_push_ranges(L, (LTS_Ranges) {
		.ptr = ptr,
		.elem_count = elem_count
	});
	return 1;
}

#define check_index(L, idx, max) \
	luaL_argcheck((L), \
		(idx) > 0, \
		2, \
		"attempt to index "LTS_RANGES_METATABLE_NAME" with non-positive index" \
	); \
	luaL_argcheck((L), \
		(idx) <= (max), \
		2, \
		"attempt to index "LTS_RANGES_METATABLE_NAME" beyond last element" \
	)

static int LTS_ranges_unpack(lua_State *L) {
	LTS_Ranges self = LTS_check_ranges(L, 1);
	int start = luaL_optinteger(L, 2, 1);
	int end = luaL_optinteger(L, 3, self.elem_count);

	check_index(L, start, self.elem_count);
	check_index(L, end, self.elem_count);

	lua_settop(L, 0);
	lua_checkstack(L, self.elem_count);
	
	for (size_t i = start - 1; i < end; i++) {
		LTS_push_range(L, self.ptr[i]);
	}
	return end - start + 1;
}

static int LTS_ranges_to_table(lua_State *L) {
	LTS_Ranges self = LTS_check_ranges(L, 1);
	
	lua_settop(L, 0);

	lua_createtable(L, self.elem_count, 0);
	for (size_t i = 1; i <= self.elem_count; i++) {
		LTS_push_range(L, self.ptr[i - 1]);
		lua_rawseti(L, 1, i);
	}
	return 1;
}

static int LTS_ranges_copy(lua_State *L) {
	LTS_Ranges self = LTS_check_ranges(L, 1);

	TSRange *ptr = malloc(self.elem_count * sizeof *ptr);
	memcpy(ptr, self.ptr, self.elem_count * sizeof *ptr);

	LTS_push_ranges(L, (LTS_Ranges) {
		.ptr = ptr,
		.elem_count = self.elem_count
	});
	return 1;
}

static int LTS_ranges_at(lua_State *L) {
	LTS_Ranges self = LTS_check_ranges(L, 1);
	lua_Integer idx = luaL_checkinteger(L, 2);

	check_index(L, idx, self.elem_count);

	LTS_push_range(L, self.ptr[idx - 1]);
	return 1;
}

static int LTS_ranges_set_at(lua_State *L) {
	LTS_Ranges self = LTS_check_ranges(L, 1);
	lua_Integer idx = luaL_checkinteger(L, 2);
	TSRange range = LTS_check_range(L, 3);

	check_index(L, idx, self.elem_count);

	self.ptr[idx - 1] = range;
	return 0;
}

#undef check_index

static int LTS_ranges_len(lua_State *L) {
	LTS_Ranges self = LTS_check_ranges(L, 1);

	lua_pushinteger(L, self.elem_count);
	return 1;
}

static int LTS_ranges_eq(lua_State *L) {
	LTS_Ranges self = LTS_check_ranges(L, 1);
	LTS_Ranges other = LTS_check_ranges(L, 2);

	if (self.elem_count == other.elem_count) {
		int cmp = memcmp(self.ptr, other.ptr, self.elem_count * sizeof(TSRange));
		lua_pushboolean(L, !cmp);
	} else {
		lua_pushboolean(L, 0);
	}
	return 1;
}

static const luaL_Reg funcs[] = {
	{ "new", LTS_ranges_new },
	{ "pack", LTS_ranges_pack },
	{ "from_table", LTS_ranges_new },
	{ NULL, NULL }
};

static const luaL_Reg methods[] = {
	{ "unpack", LTS_ranges_unpack },
	{ "to_table", LTS_ranges_to_table },
	{ "copy", LTS_ranges_copy },
	{ "at", LTS_ranges_at },
	{ "set_at", LTS_ranges_set_at },
	{ NULL, NULL }
};

static const luaL_Reg metamethods[] = {
	{ "__len", LTS_ranges_len },
	{ "__eq", LTS_ranges_eq },
	{ "__gc", LTS_ranges_delete },
	{ NULL, NULL }
};

void LTS_make_metatable_ranges(lua_State *L) {
	LTS_util_make_metatable(L, LTS_RANGES_METATABLE_NAME, methods, metamethods);
}

void LTS_make_functable_ranges(lua_State *L) {
	LTS_util_make_functable(L, LTS_RANGES_FUNCTABLE_NAME, funcs);
}
