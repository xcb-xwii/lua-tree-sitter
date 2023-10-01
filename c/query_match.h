#pragma once
#ifndef LTS_QUERY_MATCH_H
#define LTS_QUERY_MATCH_H

#include <lua.h>

#include <tree_sitter/api.h>

#define LTS_QUERY_MATCH_FUNCTABLE_NAME "QueryMatch"
#define LTS_QUERY_MATCH_METATABLE_NAME "lua_tree_sitter.QueryMatch"

typedef struct {
	TSQueryMatch match;
	int cursor_ref;
} LTS_QueryMatch;

void LTS_make_metatable_query_match(lua_State *L);
void LTS_make_functable_query_match(lua_State *L);
void LTS_push_query_match(lua_State *L, TSQueryMatch target, int cursor_idx);
TSQueryMatch LTS_check_query_match(lua_State *L, int idx);
LTS_QueryMatch LTS_check_lts_query_match(lua_State *L, int idx);

#endif