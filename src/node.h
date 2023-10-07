#pragma once
#ifndef LTS_NODE_H
#define LTS_NODE_H

#include <lua.h>

#include <tree_sitter/api.h>

#define LTS_NODE_FUNCTABLE_NAME "Node"
#define LTS_NODE_METATABLE_NAME "tree_sitter.Node"

typedef struct {
	TSNode node;
	int tree_ref;
} LTS_Node;

void LTS_make_metatable_node(lua_State *L);
void LTS_make_functable_node(lua_State *L);
void LTS_push_node(lua_State *L, TSNode target, int tree_idx);
TSNode *LTS_check_node(lua_State *L, int idx);
LTS_Node *LTS_check_lts_node(lua_State *L, int idx);

#endif
