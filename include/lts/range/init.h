#pragma once
#ifndef LTS_RANGE_H
#define LTS_RANGE_H

#include <lua.h>

#include <tree_sitter/api.h>

#define LTS_RANGE_FUNCTABLE_NAME "Range"
#define LTS_RANGE_METATABLE_NAME "tree_sitter.Range"

void LTS_setup_range(lua_State *L);
void LTS_push_range(lua_State *L, TSRange target);
TSRange *LTS_check_range(lua_State *L, int idx);

#endif
