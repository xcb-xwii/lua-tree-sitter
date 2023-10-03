#pragma once
#ifndef LTS_POINT_H
#define LTS_POINT_H

#include <lua.h>

#include <tree_sitter/api.h>

#define LTS_POINT_FUNCTABLE_NAME "Point"
#define LTS_POINT_METATABLE_NAME "tree_sitter.Point"

void LTS_make_metatable_point(lua_State *L);
void LTS_make_functable_point(lua_State *L);
void LTS_push_point(lua_State *L, TSPoint target);
TSPoint *LTS_check_point(lua_State *L, int idx);

#endif
