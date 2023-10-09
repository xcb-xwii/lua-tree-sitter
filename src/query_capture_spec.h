#pragma once
#ifndef LTS_QUERY_CAPTURE_SPEC_H
#define LTS_QUERY_CAPTURE_SPEC_H

#include <lua.h>

#include <tree_sitter/api.h>

#include "query_match.h"

#define LTS_QUERY_CAPTURE_SPEC_FUNCTABLE_NAME "QueryCaptureSpec"
#define LTS_QUERY_CAPTURE_SPEC_METATABLE_NAME "tree_sitter.QueryCaptureSpec"

typedef struct {
	int capture_id;
	TSQuantifier quantifier;
	LTS_QueryMatch *match; int match_ref;
} LTS_QueryCaptureSpec;

void LTS_setup_query_capture_spec(lua_State *L);
void LTS_push_query_capture_spec(lua_State *L, int capture_id, int match_idx);
LTS_QueryCaptureSpec *LTS_check_query_capture_spec(lua_State *L, int idx);

#endif
