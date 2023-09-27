#pragma once
#ifndef LTS_INPUT_H
#define LTS_INPUT_H

#include <lua.h>

#include <tree_sitter/api.h>

typedef enum {
	LTS_INPUT_OK,
	LTS_INPUT_RTERROR,
	LTS_INPUT_RETTYPE,
} LTS_InputStatus;

typedef struct {
	lua_State *L;
	LTS_InputStatus status;
} LTS_InputContext;

TSInput LTS_input_new(lua_State *L, int idx);
void LTS_input_delete(TSInput self);
LTS_InputStatus LTS_input_get_status(TSInput self);

#endif
