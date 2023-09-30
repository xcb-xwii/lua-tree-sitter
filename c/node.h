#pragma once
#ifndef LTS_NODE_H
#define LTS_NODE_H

#include <lua.h>

#include <tree_sitter/api.h>

#define LTS_NODE_FUNCTABLE_NAME "TSNode"
#define LTS_NODE_METATABLE_NAME "lua_tree_sitter.TSNode"

void LTS_make_metatable_node(lua_State *L);
void LTS_make_functable_node(lua_State *L);
void LTS_push_node(lua_State *L, TSNode target, int tree_idx);
TSNode LTS_check_node(lua_State *L, int idx);

#endif
