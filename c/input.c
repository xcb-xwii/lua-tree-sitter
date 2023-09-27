#include "input.h"

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include "point.h"
#include "util.h"

static const char *LTS_input_read(
	void *payload,
	uint32_t byte_index,
	TSPoint position,
	uint32_t *bytes_read
) {
	LTS_InputContext *ctx = payload;
	lua_State *L = ctx->L;

	lua_pushvalue(L, -1);
	lua_pushinteger(L, byte_index);
	LTS_push_point(L, position);
	if (lua_pcall(L, 2, 1, 0) != 0) {
		ctx->status = LTS_INPUT_RTERROR;
		*bytes_read = 0;
		return NULL;
	}

	if (lua_isnil(L, -1)) {
		*bytes_read = 0;
		return NULL;
	}

	if (lua_type(L, -1) != LUA_TSTRING) {
		ctx->status = LTS_INPUT_RETTYPE;
		*bytes_read = 0;
		return NULL;
	}

	size_t len;
	const char *str = lua_tolstring(L, -1, &len);
	*bytes_read = len;
	lua_pop(L, 1);

	return str;
}

TSInput LTS_input_new(lua_State *L, int idx) {
	TSInput self = {};

	luaL_checktype(L, idx, LUA_TFUNCTION);

	LTS_InputContext *ctx = malloc(sizeof *ctx);
	ctx->L = L;
	ctx->status = LTS_INPUT_OK;

	self.payload = ctx;
	self.read = LTS_input_read;
	self.encoding = TSInputEncodingUTF8;

	return self;
}

void LTS_input_delete(TSInput self) {
	free(self.payload);
}

LTS_InputStatus LTS_input_get_status(TSInput self) {
	return ((LTS_InputContext *) (self.payload))->status;
}
