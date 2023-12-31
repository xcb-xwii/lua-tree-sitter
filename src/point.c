#include <lts/point.h>

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include <lts/util.h>

void LTS_push_point(lua_State *L, TSPoint target) {
	TSPoint *ud = lua_newuserdata(L, sizeof *ud);
	*ud = target;
	LTS_util_set_metatable(L, LTS_POINT_METATABLE_NAME);
}

TSPoint *LTS_check_point(lua_State *L, int idx) {
	return luaL_checkudata(L, idx, LTS_POINT_METATABLE_NAME);
}

static int LTS_point_new(lua_State *L) {
	TSPoint self = {
		.row = luaL_checkinteger(L, 1),
		.column = luaL_checkinteger(L, 2)
	};

	LTS_push_point(L, self);
	return 1;
}

static int LTS_point_unpack(lua_State *L) {
	TSPoint self = *LTS_check_point(L, 1);

	lua_pushinteger(L, self.row);
	lua_pushinteger(L, self.column);
	return 2;
}

static int LTS_point_row(lua_State *L) {
	TSPoint self = *LTS_check_point(L, 1);

	lua_pushinteger(L, self.row);
	return 1;
}

static int LTS_point_column(lua_State *L) {
	TSPoint self = *LTS_check_point(L, 1);

	lua_pushinteger(L, self.column);
	return 1;
}

static int LTS_point_eq(lua_State *L) {
	TSPoint self = *LTS_check_point(L, 1);
	TSPoint other = *LTS_check_point(L, 2);

	lua_pushboolean(L, self.row == other.row && self.column == other.column);
	return 1;
}

static int LTS_point_lt(lua_State *L) {
	TSPoint self = *LTS_check_point(L, 1);
	TSPoint other = *LTS_check_point(L, 2);

	lua_pushboolean(L,
		self.row < other.row ||
		(self.row == other.row && self.column < other.column));
	return 1;
}

static int LTS_point_le(lua_State *L) {
	TSPoint self = *LTS_check_point(L, 1);
	TSPoint other = *LTS_check_point(L, 2);

	lua_pushboolean(L,
		self.row < other.row ||
		(self.row == other.row && self.column == other.column));
	return 1;
}

static const luaL_Reg methods[] = {
	{ "unpack", LTS_point_unpack },
	{ "row", LTS_point_row },
	{ "column", LTS_point_column },
	{ NULL, NULL }
};

static const luaL_Reg metamethods[] = {
	{ "__eq", LTS_point_eq },
	{ "__lt", LTS_point_lt },
	{ "__le", LTS_point_le },
	{ NULL, NULL }
};

static const luaL_Reg funcs[] = {
	{ "new", LTS_point_new },
	{ "pack", LTS_point_new },
	{ NULL, NULL }
};

void LTS_setup_point(lua_State *L) {
	LTS_util_make_metatable(L, LTS_POINT_METATABLE_NAME, methods, metamethods);
	LTS_util_make_functable(L, LTS_POINT_FUNCTABLE_NAME, funcs);
}
