#pragma once
#ifndef LTS_QUERY_CAPTURE_H
#define LTS_QUERY_CAPTURE_H

#include <lua.h>

#include <tree_sitter/api.h>

#define LTS_QUERY_CAPTURE_FUNCTABLE_NAME "QueryCapture"
#define LTS_QUERY_CAPTURE_METATABLE_NAME "lua_tree_sitter.QueryCapture"

typedef struct {
	TSQueryCapture capture;
	int match_ref;
} LTS_QueryCapture;

void LTS_make_metatable_query_capture(lua_State *L);
void LTS_make_functable_query_capture(lua_State *L);
void LTS_push_query_capture(lua_State *L, TSQueryCapture target, int match_idx);
TSQueryCapture LTS_check_query_capture(lua_State *L, int idx);
LTS_QueryCapture LTS_check_lts_query_capture(lua_State *L, int idx);

#endif
