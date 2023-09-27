#include "util.h"

#include <lua.h>
#include <lauxlib.h>

void LTS_util_set_funcs(lua_State *L, const luaL_Reg reg[]) {
	if (!reg) return;
	for (; reg->name != NULL; reg++) {
		lua_pushcfunction(L, reg->func);
		lua_setfield(L, -2, reg->name);
	}
}

void LTS_util_make_functable(
	lua_State *L,
	const char *name,
	const luaL_Reg reg[]
) {
	lua_newtable(L);
	LTS_util_set_funcs(L, reg);
	lua_setfield(L, -2, name);
}

void LTS_util_make_metatable(
	lua_State *L,
	const char *name,
	const luaL_Reg methods[],
	const luaL_Reg metamethods[]
) {
	luaL_newmetatable(L, name);
	LTS_util_set_funcs(L, metamethods);

	lua_newtable(L);
	LTS_util_set_funcs(L, methods);
	lua_setfield(L, -2, "__index");
	
	lua_pushstring(L, name);
	lua_setfield(L, -2, "__name");
}

void LTS_util_set_metatable(lua_State *L, const char *name) {
	luaL_getmetatable(L, name);
	lua_setmetatable(L, -2);
}
