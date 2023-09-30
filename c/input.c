#include "input.h"

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include "point.h"
#include "util.h"

typedef struct {
	lua_State *L;
	int read_ref;
	LTS_InputStatus status;
} LTS_InputContext;

static const char *read(
	void *payload,
	uint32_t byte_index,
	TSPoint position,
	uint32_t *bytes_read
) {
	LTS_InputContext *ctx = payload;
	lua_State *L = ctx->L;

	lua_rawgeti(L, LUA_REGISTRYINDEX, ctx->read_ref);
	lua_pushinteger(L, byte_index);
	LTS_push_point(L, position);
	if (lua_pcall(L, 2, 1, 0) != 0) {
		ctx->status = LTS_INPUT_RTERROR;
		goto fail;
	}

	if (lua_isnil(L, -1)) {
		lua_pop(L, 1);
		goto fail;
	}

	if (lua_type(L, -1) != LUA_TSTRING) {
		ctx->status = LTS_INPUT_RETTYPE;
		goto fail;
	}

	size_t len;
	const char *str = lua_tolstring(L, -1, &len);
	*bytes_read = len;
	lua_pop(L, 1);

	return str;

fail:
	*bytes_read = 0;
	return NULL;
}

void LTS_push_input(lua_State *L, TSInput target) {
	TSInput *ud = lua_newuserdata(L, sizeof *ud);
	*ud = target;
	LTS_util_set_metatable(L, LTS_INPUT_METATABLE_NAME);
}

TSInput LTS_check_input(lua_State *L, int idx) {
	return *(TSInput *) luaL_checkudata(L, idx, LTS_INPUT_METATABLE_NAME);
}

int LTS_input_new(lua_State *L) {
	TSInput self = {};

	luaL_checktype(L, 1, LUA_TFUNCTION);
	lua_settop(L, 1);

	LTS_InputContext *ctx = malloc(sizeof *ctx);
	ctx->L = L;
	ctx->read_ref = luaL_ref(L, LUA_REGISTRYINDEX);
	ctx->status = LTS_INPUT_OK;

	self.payload = ctx;
	self.read = read;
	self.encoding = TSInputEncodingUTF8;

	LTS_push_input(L, self);
	return 1;
}

int LTS_input_delete(lua_State *L) {
	TSInput self = LTS_check_input(L, 1);

	LTS_InputContext *ctx = self.payload;
	luaL_unref(L, LUA_REGISTRYINDEX, ctx->read_ref);
	free(ctx);
	return 0;
}

int LTS_input_read(lua_State *L) {
	TSInput self = LTS_check_input(L, 1);

	lua_rawgeti(L, ((LTS_InputContext *) (self.payload))->read_ref, LUA_REGISTRYINDEX);
	return 1;
}

LTS_InputStatus LTS_input_get_status(TSInput self) {
	return ((LTS_InputContext *) (self.payload))->status;
}

void LTS_input_reset_status(TSInput self) {
	((LTS_InputContext *) (self.payload))->status = LTS_INPUT_OK;
}

static const luaL_Reg methods[] = {
	{ "read", LTS_input_read },
	{ NULL, NULL }
};

static const luaL_Reg metamethods[] = {
	{ "__gc", LTS_input_delete },
	{ NULL, NULL }
};

static const luaL_Reg funcs[] = {
	{ "new", LTS_input_new },
	{ "pack", LTS_input_new },
	{ "unpack", LTS_input_read },
	{ NULL, NULL }
};

void LTS_make_metatable_input(lua_State *L) {
	LTS_util_make_metatable(L, LTS_INPUT_METATABLE_NAME, methods, metamethods);
}

void LTS_make_functable_input(lua_State *L) {
	LTS_util_make_functable(L, LTS_INPUT_FUNCTABLE_NAME, funcs);
}
