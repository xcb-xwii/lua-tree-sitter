#include <lts/query/quantified_capture.h>

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include <stdint.h>

#include <lts/node.h>
#include <lts/query/capture.h>
#include <lts/query/match.h>
#include <lts/util.h>

void LTS_push_query_quantified_capture(lua_State *L, int capture_id, int match_idx) {
	LTS_QueryQuantifiedCapture *ud = lua_newuserdata(L, sizeof *ud);
	ud->capture_id = capture_id;

	LTS_QueryMatch *match = lua_touserdata(L, match_idx);
	ud->match = match;
	lua_pushvalue(L, match_idx);
	ud->match_ref = luaL_ref(L, LUA_REGISTRYINDEX);

	ud->quantifier = ts_query_capture_quantifier_for_id(
		match->cursor->query->query,
		match->match.pattern_index,
		capture_id
	);

	LTS_util_set_metatable(L, LTS_QUERY_QUANTIFIED_CAPTURE_METATABLE_NAME);
}

LTS_QueryQuantifiedCapture *LTS_check_query_quantified_capture(lua_State *L, int idx) {
	return luaL_checkudata(L, idx, LTS_QUERY_QUANTIFIED_CAPTURE_METATABLE_NAME);
}

static int LTS_query_quantified_capture_delete(lua_State *L) {
	LTS_QueryQuantifiedCapture self = *LTS_log_gc(LTS_check_query_quantified_capture(L, 1), LTS_QUERY_QUANTIFIED_CAPTURE_METATABLE_NAME);
	
	luaL_unref(L, LUA_REGISTRYINDEX, self.match_ref);
	return 0;
}

static int LTS_query_quantified_capture_index(lua_State *L) {
	LTS_QueryQuantifiedCapture self = *LTS_check_query_quantified_capture(L, 1);
	
	lua_pushinteger(L, self.capture_id);
	return 1;
}

static int LTS_query_quantified_capture_match(lua_State *L) {
	LTS_QueryQuantifiedCapture self = *LTS_check_query_quantified_capture(L, 1);

	lua_rawgeti(L, LUA_REGISTRYINDEX, self.match_ref);
	return 1;
}

static int LTS_query_quantified_capture_name(lua_State *L) {
	LTS_QueryQuantifiedCapture self = *LTS_check_query_quantified_capture(L, 1);

	LTS_push_query_capture_name_for_id(*self.match->cursor->query, self.capture_id);
	return 1;
}

static int LTS_query_quantified_capture_quantifier(lua_State *L) {
	LTS_QueryQuantifiedCapture self = *LTS_check_query_quantified_capture(L, 1);

	switch (self.quantifier) {
	case TSQuantifierZero:
		lua_pushliteral(L, "Zero");
		break;
	case TSQuantifierZeroOrOne:
		lua_pushliteral(L, "ZeroOrOne");
		break;
	case TSQuantifierOne:
		lua_pushliteral(L, "One");
		break;
	case TSQuantifierZeroOrMore:
		lua_pushliteral(L, "ZeroOrMore");
		break;
	case TSQuantifierOneOrMore:
		lua_pushliteral(L, "OneOrMore");
		break;
	}
	return 1;
}

static int LTS_query_quantified_capture_one_capture(lua_State *L) {
	LTS_QueryQuantifiedCapture self = *LTS_check_query_quantified_capture(L, 1);

	if (self.quantifier == TSQuantifierZero) {
		lua_pushnil(L);
	} else {
		TSQueryMatch match = self.match->match;
		for (uint16_t j = 0; j < match.capture_count; j++) {
			if (match.captures[j].index == self.capture_id) {
				lua_settop(L, 1);
				lua_rawgeti(L, LUA_REGISTRYINDEX, self.match_ref);
				LTS_push_query_capture(L, match.captures[j], 2);
				return 1;
			}
		}
		lua_pushnil(L);
	}

	return 1;
}

static int LTS_query_quantified_capture_one_node(lua_State *L) {
	LTS_QueryQuantifiedCapture self = *LTS_check_query_quantified_capture(L, 1);

	if (self.quantifier == TSQuantifierZero) {
		lua_pushnil(L);
	} else {
		TSQueryMatch match = self.match->match;
		for (uint16_t j = 0; j < match.capture_count; j++) {
			if (match.captures[j].index == self.capture_id) {
				lua_settop(L, 1);
				lua_rawgeti(L, LUA_REGISTRYINDEX, self.match->cursor->node->tree_ref);
				LTS_push_node(L, match.captures[j].node, 2);
				return 1;
			}
		}
		lua_pushnil(L);
	}

	return 1;
}

static int LTS_query_quantified_capture_captures(lua_State *L) {
	LTS_QueryQuantifiedCapture self = *LTS_check_query_quantified_capture(L, 1);

	TSQueryMatch match = self.match->match;
	uint16_t count = 0;
	for (uint16_t i = 0; i < match.capture_count; i++) {
		if (match.captures[i].index == self.capture_id) count++;
	}

	lua_settop(L, 1);
	lua_rawgeti(L, LUA_REGISTRYINDEX, self.match_ref);
	lua_createtable(L, count, 0);
	for (uint16_t size = 0, i = 0; size < count; i++) {
		if (match.captures[i].index == self.capture_id) {
			LTS_push_query_capture(L, match.captures[i], 2);
			lua_rawseti(L, -2, ++size);
		}
	}
	return 1;
}

static int LTS_query_quantified_capture_nodes(lua_State *L) {
	LTS_QueryQuantifiedCapture self = *LTS_check_query_quantified_capture(L, 1);

	TSQueryMatch match = self.match->match;
	uint16_t count = 0;
	for (uint16_t i = 0; i < match.capture_count; i++) {
		if (match.captures[i].index == self.capture_id) count++;
	}

	lua_settop(L, 1);
	lua_rawgeti(L, LUA_REGISTRYINDEX, self.match->cursor->node->tree_ref);
	lua_createtable(L, count, 0);
	for (uint16_t size = 0, i = 0; size < count; i++) {
		if (match.captures[i].index == self.capture_id) {
			LTS_push_node(L, match.captures[i].node, 2);
			lua_rawseti(L, -2, ++size);
		}
	}
	return 1;
}

static const luaL_Reg methods[] = {
	{ "index", LTS_query_quantified_capture_index },
	{ "match", LTS_query_quantified_capture_match },
	{ "name", LTS_query_quantified_capture_name },
	{ "quantifier", LTS_query_quantified_capture_quantifier },
	{ "one_capture", LTS_query_quantified_capture_one_capture },
	{ "one_node", LTS_query_quantified_capture_one_node },
	{ "captures", LTS_query_quantified_capture_captures },
	{ "nodes", LTS_query_quantified_capture_nodes },
	{ NULL, NULL }
};

static const luaL_Reg metamethods[] = {
	{ "__gc", LTS_query_quantified_capture_delete },
	{ NULL, NULL }
};

void LTS_setup_query_quantified_capture(lua_State *L) {
	LTS_util_make_metatable(L, LTS_QUERY_QUANTIFIED_CAPTURE_METATABLE_NAME, methods, metamethods);
}
