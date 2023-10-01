#include "input_edit.h"

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include "point.h"
#include "util.h"

void LTS_push_input_edit(lua_State *L, TSInputEdit *target) {
	TSInputEdit *ud = lua_newuserdata(L, sizeof *ud);
	*ud = *target;
	LTS_util_set_metatable(L, LTS_INPUT_EDIT_METATABLE_NAME);
}

TSInputEdit *LTS_check_input_edit(lua_State *L, int idx) {
	return (TSInputEdit *) luaL_checkudata(L, idx, LTS_INPUT_EDIT_METATABLE_NAME);
}

static int LTS_input_edit_new(lua_State *L) {
	TSInputEdit self = {
		.start_byte = luaL_checkinteger(L, 1),
		.old_end_byte = luaL_checkinteger(L, 2),
		.new_end_byte = luaL_checkinteger(L, 3),
		.start_point = LTS_check_point(L, 4),
		.old_end_point = LTS_check_point(L, 5),
		.new_end_point = LTS_check_point(L, 6)
	};

	LTS_push_input_edit(L, &self);
	return 1;
}

static int LTS_input_edit_unpack(lua_State *L) {
	TSInputEdit *self = LTS_check_input_edit(L, 1);

	lua_pushinteger(L, self->start_byte);
	lua_pushinteger(L, self->old_end_byte);
	lua_pushinteger(L, self->new_end_byte);
	LTS_push_point(L, self->start_point);
	LTS_push_point(L, self->old_end_point);
	LTS_push_point(L, self->new_end_point);
	return 6;
}

static int LTS_input_edit_start_byte(lua_State *L) {
	TSInputEdit *self = LTS_check_input_edit(L, 1);

	lua_pushinteger(L, self->start_byte);
	return 1;
}

static int LTS_input_edit_old_end_byte(lua_State *L) {
	TSInputEdit *self = LTS_check_input_edit(L, 1);

	lua_pushinteger(L, self->old_end_byte);
	return 1;
}

static int LTS_input_edit_new_end_byte(lua_State *L) {
	TSInputEdit *self = LTS_check_input_edit(L, 1);

	lua_pushinteger(L, self->new_end_byte);
	return 1;
}

static int LTS_input_edit_start_point(lua_State *L) {
	TSInputEdit *self = LTS_check_input_edit(L, 1);

	LTS_push_point(L, self->start_point);
	return 1;
}

static int LTS_input_edit_old_end_point(lua_State *L) {
	TSInputEdit *self = LTS_check_input_edit(L, 1);

	LTS_push_point(L, self->old_end_point);
	return 1;
}

static int LTS_input_edit_new_end_point(lua_State *L) {
	TSInputEdit *self = LTS_check_input_edit(L, 1);

	LTS_push_point(L, self->new_end_point);
	return 1;
}

static const luaL_Reg methods[] = {
	{ "unpack", LTS_input_edit_unpack },
	{ "start_byte", LTS_input_edit_start_byte },
	{ "old_end_byte", LTS_input_edit_old_end_byte },
	{ "new_end_byte", LTS_input_edit_new_end_byte },
	{ "start_point", LTS_input_edit_start_point },
	{ "old_end_point", LTS_input_edit_old_end_point },
	{ "new_end_point", LTS_input_edit_new_end_point },
	{ NULL, NULL }
};

static const luaL_Reg metamethods[] = {
	//{ "__eq", LTS_input_edit_eq },
	{ NULL, NULL }
};

static const luaL_Reg funcs[] = {
	{ "new", LTS_input_edit_new },
	{ "pack", LTS_input_edit_new },
	{ NULL, NULL }
};

void LTS_make_metatable_input_edit(lua_State *L) {
	LTS_util_make_metatable(L, LTS_INPUT_EDIT_METATABLE_NAME, methods, metamethods);
}

void LTS_make_functable_input_edit(lua_State *L) {
	LTS_util_make_functable(L, LTS_INPUT_EDIT_FUNCTABLE_NAME, funcs);
}
