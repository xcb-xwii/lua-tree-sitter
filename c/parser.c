#include "parser.h"

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include "input.h"
#include "language.h"
#include "tree.h"
#include "util.h"

void LTS_push_parser(lua_State *L, TSParser *target) {
	TSParser **ud = lua_newuserdata(L, sizeof *ud);
	*ud = target;
	LTS_util_set_metatable(L, LTS_PARSER_METATABLE_NAME);
}

TSParser *LTS_check_parser(lua_State *L, int idx) {
	return *(TSParser **) luaL_checkudata(L, idx, LTS_PARSER_METATABLE_NAME);
}

static int LTS_parser_new(lua_State *L) {
	TSParser *self = ts_parser_new();

	LTS_push_parser(L, self);
	return 1;
}

static int LTS_parser_delete(lua_State *L) {
	TSParser *self = LTS_check_parser(L, 1);

	ts_parser_delete(self);
	return 0;
}

static int LTS_parser_language(lua_State *L) {
	TSParser *self = LTS_check_parser(L, 1);

	LTS_push_language(L, (TSLanguage *) ts_parser_language(self));
	return 1;
}

static int LTS_parser_set_language(lua_State *L) {
	TSParser *self = LTS_check_parser(L, 1);
	TSLanguage *lang = LTS_check_language(L, 2);

	lua_pushboolean(L, ts_parser_set_language(self, lang));
	return 1;
}

static int LTS_parser_parse(lua_State *L) {
	TSParser *self = LTS_check_parser(L, 1);
	TSTree *old_tree = lua_isnil(L, 2) ? NULL : LTS_check_tree(L, 2);
	TSInput input = LTS_check_input(L, 3);

	LTS_input_reset_status(input);
	TSTree *tree = ts_parser_parse(self, old_tree, input);

	switch (LTS_input_get_status(input)) {
	case LTS_INPUT_RTERROR:
		ts_tree_delete(tree);
		return luaL_error(L,
			"error while executing read function: %s",
			lua_tostring(L, -1)
		);

	case LTS_INPUT_RETTYPE:
		ts_tree_delete(tree);
		return luaL_error(L,
			"bad return value from read function (string expected, got %s)",
			lua_typename(L, lua_type(L, -1))
		);

	default:
		break;
	}

	if (!tree) {
		lua_pushnil(L);
		return 1;
	}

	LTS_push_tree(L, tree);
	return 1;
}

static const luaL_Reg metamethods[] = {
	{ "__gc", LTS_parser_delete },
	{ NULL, NULL }
};

static const luaL_Reg funcs[] = {
	{ "new", LTS_parser_new },
	{ "language", LTS_parser_language },
	{ "set_language", LTS_parser_set_language },
	//{ "included_ranges", LTS_parser_included_ranges },
	//{ "set_included_ranges", LTS_parser_set_included_ranges },
	{ "parse", LTS_parser_parse },
	//{ "parse_string", LTS_parser_parse_string },
	{ NULL, NULL }
};

void LTS_make_metatable_parser(lua_State *L) {
	LTS_util_make_metatable(L, LTS_PARSER_METATABLE_NAME, NULL, metamethods);
}

void LTS_make_functable_parser(lua_State *L) {
	LTS_util_make_functable(L, LTS_PARSER_FUNCTABLE_NAME, funcs);
}
