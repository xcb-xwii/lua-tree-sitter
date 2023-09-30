#pragma once
#ifndef LTS_RANGE_H
#define LTS_RANGE_H

#include <lua.h>

#include <tree_sitter/api.h>

#define LTS_RANGE_FUNCTABLE_NAME "TSRange"
#define LTS_RANGE_METATABLE_NAME "lua_tree_sitter.TSRange"

void LTS_make_metatable_range(lua_State *L);
void LTS_make_functable_range(lua_State *L);
void LTS_push_range(lua_State *L, TSRange *target);
TSRange *LTS_check_range(lua_State *L, int idx);

#endif
