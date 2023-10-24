#pragma once
#ifndef LTS_QUERY_RUNNER_H
#define LTS_QUERY_RUNNER_H

#include <lua.h>

#include <tree_sitter/api.h>

#include <lts/query/match.h>

#define LTS_QUERY_RUNNER_FUNCTABLE_NAME "Runner"
#define LTS_QUERY_RUNNER_METATABLE_NAME "tree_sitter.Query.Runner"

typedef struct {
	int predicates_ref;
	int setup_ref;
} LTS_QueryRunner;

void LTS_setup_query_runner(lua_State *L);
void LTS_push_query_runner(lua_State *L, LTS_QueryRunner target);
LTS_QueryRunner *LTS_check_query_runner(lua_State *L, int idx);

#endif
