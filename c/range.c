#include "range.h"

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include "point.h"
#include "util.h"

void LTS_push_range(lua_State *L, TSRange target) {
	TSRange *ud = lua_newuserdata(L, sizeof *ud);
	*ud = target;
	LTS_util_set_metatable(L, LTS_RANGE_METATABLE_NAME);
}

TSRange LTS_check_range(lua_State *L, int idx) {
	return *(TSRange *) luaL_checkudata(L, idx, LTS_RANGE_METATABLE_NAME);
}

static int LTS_range_new(lua_State *L) {
	TSRange self = {
		.start_point = LTS_check_point(L, 1),
		.end_point = LTS_check_point(L, 2),
		.start_byte = luaL_checkinteger(L, 3),
		.end_byte = luaL_checkinteger(L, 4),
	};

	LTS_push_range(L, self);
	return 1;
}

static int LTS_range_unpack(lua_State *L) {
	TSRange self = LTS_check_range(L, 1);

	LTS_push_point(L, self.start_point);
	LTS_push_point(L, self.end_point);
	lua_pushinteger(L, self.start_byte);
	lua_pushinteger(L, self.end_byte);
	return 4;
}

static int LTS_range_start_point(lua_State *L) {
	TSRange self = LTS_check_range(L, 1);

	LTS_push_point(L, self.start_point);
	return 1;
}

static int LTS_range_end_point(lua_State *L) {
	TSRange self = LTS_check_range(L, 1);

	LTS_push_point(L, self.end_point);
	return 1;
}

static int LTS_range_start_byte(lua_State *L) {
	TSRange self = LTS_check_range(L, 1);

	lua_pushinteger(L, self.start_byte);
	return 1;
}

static int LTS_range_end_byte(lua_State *L) {
	TSRange self = LTS_check_range(L, 1);

	lua_pushinteger(L, self.end_byte);
	return 1;
}

static const luaL_Reg methods[] = {
	{ "unpack", LTS_range_unpack },
	//{ "to_table", LTS_range_to_table },
	{ "start_byte", LTS_range_start_byte },
	{ "end_byte", LTS_range_end_byte },
	{ "start_point", LTS_range_start_point },
	{ "end_point", LTS_range_end_point },
	{ NULL, NULL }
};

static const luaL_Reg metamethods[] = {
	//{ "__eq", LTS_range_eq },
	{ NULL, NULL }
};

static const luaL_Reg funcs[] = {
	{ "new", LTS_range_new },
	{ "pack", LTS_range_new },
	//{ "from_table", LTS_range_from_table },
	{ NULL, NULL }
};

void LTS_make_metatable_range(lua_State *L) {
	LTS_util_make_metatable(L, LTS_RANGE_METATABLE_NAME, methods, metamethods);
}

void LTS_make_functable_range(lua_State *L) {
	LTS_util_make_functable(L, LTS_RANGE_FUNCTABLE_NAME, funcs);
}
