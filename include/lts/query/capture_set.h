#pragma once
#ifndef LTS_QUERY_CAPTURE_SET_H
#define LTS_QUERY_CAPTURE_SET_H

#include <lua.h>

#include <tree_sitter/api.h>

#include <lts/query/match.h>

#define LTS_QUERY_CAPTURE_SET_FUNCTABLE_NAME "CaptureSet"
#define LTS_QUERY_CAPTURE_SET_METATABLE_NAME "tree_sitter.Query.CaptureSet"

typedef struct {
	int capture_id;
	TSQuantifier quantifier;
	LTS_QueryMatch *match; int match_ref;
} LTS_QueryCaptureSet;

void LTS_setup_query_capture_set(lua_State *L);
void LTS_push_query_capture_set(lua_State *L, int capture_id, int match_idx);
LTS_QueryCaptureSet *LTS_check_query_capture_set(lua_State *L, int idx);

#endif
