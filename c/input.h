#pragma once
#ifndef LTS_INPUT_H
#define LTS_INPUT_H

#include <lua.h>

#include <tree_sitter/api.h>

#define LTS_INPUT_FUNCTABLE_NAME "Input"
#define LTS_INPUT_METATABLE_NAME "lua_tree_sitter.Input"

typedef enum {
	LTS_INPUT_OK,
	LTS_INPUT_RTERROR,
	LTS_INPUT_RETTYPE,
} LTS_InputStatus;

void LTS_make_metatable_input(lua_State *L);
void LTS_make_functable_input(lua_State *L);
void LTS_push_input(lua_State *L, TSInput target);
TSInput LTS_check_input(lua_State *L, int idx);
LTS_InputStatus LTS_input_get_status(TSInput self);
void LTS_input_reset_status(TSInput self);

#endif
