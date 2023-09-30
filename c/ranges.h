#pragma once
#ifndef LTS_RANGES_H
#define LTS_RANGES_H

#include <lua.h>

#include <tree_sitter/api.h>

#include <stdint.h>

#define LTS_RANGES_FUNCTABLE_NAME "Ranges"
#define LTS_RANGES_METATABLE_NAME "lua_tree_sitter.Ranges"

typedef struct {
	TSRange *ptr;
	uint32_t elem_count;
	bool managed;
} LTS_Ranges;

void LTS_make_metatable_ranges(lua_State *L);
void LTS_make_functable_ranges(lua_State *L);
void LTS_push_ranges(lua_State *L, LTS_Ranges target);
LTS_Ranges LTS_check_ranges(lua_State *L, int idx);

#endif
