#pragma once
#ifndef LTS_ARRAY_H
#define LTS_ARRAY_H

#include <lua.h>

#include <tree_sitter/api.h>

#include <stdint.h>

#define LTS_ARRAY_FUNCTABLE_NAME "Array"
#define LTS_ARRAY_METATABLE_NAME "lua_tree_sitter.Array"

typedef struct {
	void *ptr;
	const char *mt_name;
	uint32_t elem_count;
	uint16_t elem_size;
	bool managed;
} LTS_Array;

void LTS_make_metatable_array(lua_State *L);
void LTS_make_functable_array(lua_State *L);
void LTS_push_array(lua_State *L, LTS_Array target);
LTS_Array LTS_check_array(lua_State *L, int idx);

#endif
