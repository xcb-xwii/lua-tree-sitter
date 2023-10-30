#pragma once
#ifndef LTS_QUERY_QUANTIFIED_CAPTURE_H
#define LTS_QUERY_QUANTIFIED_CAPTURE_H

#include <lua.h>

#include <tree_sitter/api.h>

#include <stdint.h>

#include <lts/query/match.h>

#define LTS_QUERY_QUANTIFIED_CAPTURE_FUNCTABLE_NAME "QuantifiedCapture"
#define LTS_QUERY_QUANTIFIED_CAPTURE_METATABLE_NAME "tree_sitter.Query.QuantifiedCapture"

typedef struct {
	uint32_t capture_id;
	TSQuantifier quantifier;
	LTS_QueryMatch *match; int match_ref;
} LTS_QueryQuantifiedCapture;

void LTS_setup_query_quantified_capture(lua_State *L);
void LTS_push_query_quantified_capture(lua_State *L, int capture_id, int match_idx);
LTS_QueryQuantifiedCapture *LTS_check_query_quantified_capture(lua_State *L, int idx);

#endif
