#pragma once
#ifndef LTS_RANGE_ARRAY_H
#define LTS_RANGE_ARRAY_H

#include <lua.h>

#include <tree_sitter/api.h>

#include <stdint.h>

#define LTS_RANGE_ARRAY_FUNCTABLE_NAME "Array"
#define LTS_RANGE_ARRAY_METATABLE_NAME "tree_sitter.Range.Array"

typedef struct {
	TSRange *ptr;
	uint32_t elem_count;
} LTS_RangeArray;

void LTS_setup_range_array(lua_State *L);
void LTS_push_range_array(lua_State *L, LTS_RangeArray target);
LTS_RangeArray *LTS_check_range_array(lua_State *L, int idx);

#endif
