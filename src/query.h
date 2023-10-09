#pragma once
#ifndef LTS_QUERY_H
#define LTS_QUERY_H

#include <lua.h>

#include <tree_sitter/api.h>

#define LTS_QUERY_FUNCTABLE_NAME "Query"
#define LTS_QUERY_METATABLE_NAME "tree_sitter.Query"

typedef struct {
	TSQuery *query;
	int *capture_name_refs;
	int *string_value_refs;
} LTS_Query;

void LTS_setup_query(lua_State *L);
void LTS_push_query(lua_State *L, TSQuery *target);
TSQuery **LTS_check_query(lua_State *L, int idx);
LTS_Query *LTS_check_lts_query(lua_State *L, int idx);

#define LTS_push_query_capture_name_for_id(query, id) \
	(lua_rawgeti(L, LUA_REGISTRYINDEX, (query).capture_name_refs[id]))
#define LTS_push_query_string_value_for_id(query, id) \
	(lua_rawgeti(L, LUA_REGISTRYINDEX, (query).string_value_refs[id]))

#endif
