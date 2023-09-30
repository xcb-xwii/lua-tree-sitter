#pragma once
#ifndef LTS_TREE_H
#define LTS_TREE_H

#include <lua.h>

#include <tree_sitter/api.h>

#define LTS_TREE_FUNCTABLE_NAME "Tree"
#define LTS_TREE_METATABLE_NAME "lua_tree_sitter.Tree"

void LTS_make_metatable_tree(lua_State *L);
void LTS_make_functable_tree(lua_State *L);
void LTS_push_tree(lua_State *L, TSTree *target);
TSTree *LTS_check_tree(lua_State *L, int idx);

#endif
