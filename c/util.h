#pragma once
#ifndef LTS_UTIL_H
#define LTS_UTIL_H

#include <lua.h>
#include <lauxlib.h>

void LTS_util_set_funcs(lua_State *L, const luaL_Reg reg[]);
void LTS_util_make_functable(
	lua_State *L,
	const char *name,
	const luaL_Reg reg[]
);
void LTS_util_make_metatable(
	lua_State *L,
	const char *name,
	const luaL_Reg methods[],
	const luaL_Reg metamethods[]
);
void LTS_util_set_metatable(lua_State *L, const char *name);

#endif
