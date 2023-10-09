#pragma once
#ifndef LTS_PARSER_H
#define LTS_PARSER_H

#include <lua.h>

#include <tree_sitter/api.h>

#define LTS_PARSER_FUNCTABLE_NAME "Parser"
#define LTS_PARSER_METATABLE_NAME "tree_sitter.Parser"

void LTS_setup_parser(lua_State *L);
void LTS_push_parser(lua_State *L, TSParser *target);
TSParser **LTS_check_parser(lua_State *L, int idx);

#endif
