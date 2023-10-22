#include <lts/query/init.h>

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include <stdint.h>

#include <lts/language.h>
#include <lts/util.h>

void LTS_push_query(lua_State *L, TSQuery *target) {
	LTS_Query *ud = lua_newuserdata(L, sizeof *ud);

	ud->query = target;

	uint32_t count;
	int *refs;

	count = ts_query_capture_count(target);
	refs = malloc(sizeof *refs * count);
	for (uint32_t i = 0; i < count; i++) {
		uint32_t len;
		const char *name = ts_query_capture_name_for_id(target, i, &len);
		lua_pushlstring(L, name, len);
		refs[i] = luaL_ref(L, LUA_REGISTRYINDEX);
	}
	ud->capture_name_refs = refs;

	count = ts_query_string_count(target);
	refs = malloc(sizeof *refs * count);
	for (uint32_t i = 0; i < ts_query_string_count(target); i++) {
		uint32_t len;
		const char *name = ts_query_string_value_for_id(target, i, &len);
		lua_pushlstring(L, name, len);
		refs[i] = luaL_ref(L, LUA_REGISTRYINDEX);
	}
	ud->string_value_refs = refs;

	LTS_util_set_metatable(L, LTS_QUERY_METATABLE_NAME);
}

LTS_Query *LTS_check_lts_query(lua_State *L, int idx) {
	return luaL_checkudata(L, idx, LTS_QUERY_METATABLE_NAME);
}

TSQuery **LTS_check_query(lua_State *L, int idx) {
	return &LTS_check_lts_query(L, idx)->query;
}

#define QUERY_ERROR_CASE(type) \
case (type): \
	return luaL_error(L, \
		"bad query: error type "#type" at byte offset %d", \
		err_offset \
	)

static int LTS_query_new(lua_State *L) {
	TSLanguage *lang = *LTS_check_language(L, 1);
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
	LTS_Query self = *LTS_log_gc(LTS_check_lts_query(L, 1), LTS_QUERY_METATABLE_NAME);

	uint32_t count;

	count = ts_query_capture_count(self.query);
	for (uint32_t i = 0; i < count; i++) {
		luaL_unref(L, LUA_REGISTRYINDEX, self.capture_name_refs[i]);
	}
	free(self.capture_name_refs);

	count = ts_query_string_count(self.query);
	for (uint32_t i = 0; i < count; i++) {
		luaL_unref(L, LUA_REGISTRYINDEX, self.string_value_refs[i]);
	}
	free(self.string_value_refs);

	ts_query_delete(self.query);
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

void LTS_setup_query(lua_State *L) {
	LTS_util_make_metatable(L, LTS_QUERY_METATABLE_NAME, NULL, metamethods);
	LTS_util_make_functable(L, LTS_QUERY_FUNCTABLE_NAME, funcs);
}
