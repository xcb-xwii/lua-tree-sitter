#pragma once
#ifndef LTS_LANGUAGE_H
#define LTS_LANGUAGE_H

#include <lua.h>

#include <tree_sitter/api.h>

#define LTS_LANGUAGE_FUNCTABLE_NAME "Language"
#define LTS_LANGUAGE_METATABLE_NAME "tree_sitter.Language"

void LTS_setup_language(lua_State *L);
void LTS_push_language(lua_State *L, TSLanguage *target);
TSLanguage **LTS_check_language(lua_State *L, int idx);

#endif
