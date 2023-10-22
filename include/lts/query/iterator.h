#pragma once
#ifndef LTS_QUERY_ITERATOR_H
#define LTS_QUERY_ITERATOR_H

#include <lua.h>

#include <tree_sitter/api.h>

#include <lts/query/match.h>

#define LTS_QUERY_ITERATOR_FUNCTABLE_NAME "Iterator"
#define LTS_QUERY_ITERATOR_METATABLE_NAME "tree_sitter.Iterator"

typedef struct {
	int predicates_ref;
	bool error_on_invalid_predicate;
} LTS_QueryIterator;

void LTS_setup_query_iterator(lua_State *L);
void LTS_push_query_iterator(lua_State *L, LTS_QueryIterator target);
LTS_QueryIterator *LTS_check_query_iterator(lua_State *L, int idx);

#endif
