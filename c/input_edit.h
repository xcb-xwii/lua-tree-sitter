#pragma once
#ifndef LTS_INPUT_EDIT_H
#define LTS_INPUT_EDIT_H

#include <lua.h>

#include <tree_sitter/api.h>

#define LTS_INPUT_EDIT_FUNCTABLE_NAME "TSInputEdit"
#define LTS_INPUT_EDIT_METATABLE_NAME "lua_tree_sitter.TSInputEdit"

void LTS_make_metatable_input_edit(lua_State *L);
void LTS_make_functable_input_edit(lua_State *L);
// Note: while pushing and popping uses pointers, these objects are not stored
// as pointers, it is just used to reduce overhead of passing large structs.
void LTS_push_input_edit(lua_State *L, TSInputEdit *target);
TSInputEdit *LTS_check_input_edit(lua_State *L, int idx);

#endif
