#pragma once
#ifndef LTS_QUERY_H
#define LTS_QUERY_H

#include <lua.h>

#include <tree_sitter/api.h>

#define LTS_QUERY_FUNCTABLE_NAME "Query"
#define LTS_QUERY_METATABLE_NAME "lua_tree_sitter.Query"

void LTS_make_metatable_query(lua_State *L);
void LTS_make_functable_query(lua_State *L);
void LTS_push_query(lua_State *L, TSQuery *target);
TSQuery *LTS_check_query(lua_State *L, int idx);

#endif
