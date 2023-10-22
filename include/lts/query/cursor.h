#pragma once
#ifndef LTS_QUERY_CURSOR_H
#define LTS_QUERY_CURSOR_H

#include <lua.h>

#include <tree_sitter/api.h>

#include <lts/node.h>
#include <lts/query/init.h>

#define LTS_QUERY_CURSOR_FUNCTABLE_NAME "Cursor"
#define LTS_QUERY_CURSOR_METATABLE_NAME "tree_sitter.Query.Cursor"

typedef struct {
	TSQueryCursor *query_cursor;
	LTS_Query *query; int query_ref;
	LTS_Node *node; int node_ref;
} LTS_QueryCursor;

void LTS_setup_query_cursor(lua_State *L);
void LTS_push_query_cursor(
	lua_State *L,
	TSQueryCursor *target,
	int query_idx,
	int tree_idx
);
TSQueryCursor **LTS_check_query_cursor(lua_State *L, int idx);
LTS_QueryCursor *LTS_check_lts_query_cursor(lua_State *L, int idx);

#endif
