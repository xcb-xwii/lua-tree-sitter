#include "query.h"

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include <stdint.h>

#include "language.h"
#include "query.h"
#include "util.h"

void LTS_push_query(lua_State *L, TSQuery *target) {
	TSQuery **ud = lua_newuserdata(L, sizeof *ud);
	*ud = target;
	LTS_util_set_metatable(L, LTS_QUERY_METATABLE_NAME);
}

TSQuery *LTS_check_query(lua_State *L, int idx) {
	return *(TSQuery **) luaL_checkudata(L, idx, LTS_QUERY_METATABLE_NAME);
}

#define QUERY_ERROR_CASE(type) \
case (type): \
	return luaL_error(L, \
		"bad query: error type "#type" at byte offset %d", \
		err_offset \
	)

static int LTS_query_new(lua_State *L) {
	TSLanguage *lang = LTS_check_language(L, 1);
	size_t src_len;
	const char *src = luaL_checklstring(L, 2, &src_len);

	uint32_t err_offset;
	TSQueryError err_type;
	TSQuery *self = ts_query_new(lang, src, src_len, &err_offset, &err_type);
	switch (err_type) {
	case TSQueryErrorNone: break;
	QUERY_ERROR_CASE(TSQueryErrorSyntax);
	QUERY_ERROR_CASE(TSQueryErrorNodeType);
	QUERY_ERROR_CASE(TSQueryErrorField);
	QUERY_ERROR_CASE(TSQueryErrorCapture);
	QUERY_ERROR_CASE(TSQueryErrorStructure);
	QUERY_ERROR_CASE(TSQueryErrorLanguage);
	}

	LTS_push_query(L, self);
	return 1;
}

#undef QUERY_ERROR_CASE

static int LTS_query_delete(lua_State *L) {
	TSQuery *self = LTS_check_query(L, 1);

	ts_query_delete(self);
	return 0;
}

static const luaL_Reg metamethods[] = {
	{ "__gc", LTS_query_delete },
	{ NULL, NULL }
};

static const luaL_Reg funcs[] = {
	{ "new", LTS_query_new },
	{ NULL, NULL }
};

void LTS_make_metatable_query(lua_State *L) {
	LTS_util_make_metatable(L, LTS_QUERY_METATABLE_NAME, NULL, metamethods);
}

void LTS_make_functable_query(lua_State *L) {
	LTS_util_make_functable(L, LTS_QUERY_FUNCTABLE_NAME, funcs);
}
