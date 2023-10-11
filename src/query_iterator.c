#include "query_iterator.h"

#include <lua.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include "query.h"
#include "query_capture.h"
#include "query_capture_spec.h"
#include "query_cursor.h"
#include "query_match.h"
#include "node.h"
#include "util.h"

void LTS_push_query_iterator(lua_State *L, LTS_QueryIterator target) {
	LTS_QueryIterator *ud = lua_newuserdata(L, sizeof *ud);
	*ud = target;
	LTS_util_set_metatable(L, LTS_QUERY_ITERATOR_METATABLE_NAME);
}

LTS_QueryIterator *LTS_check_query_iterator(lua_State *L, int idx) {
	return luaL_checkudata(L, idx, LTS_QUERY_ITERATOR_METATABLE_NAME);
}

static int LTS_query_iterator_new(lua_State *L) {
	LTS_QueryIterator self = {};
	
	switch (lua_type(L, 1)) {
	case LUA_TNONE:
		self.predicates_ref = LUA_REFNIL;
		self.error_on_invalid_predicate = false;
		break;

	case LUA_TNIL:
	case LUA_TTABLE:
		self.error_on_invalid_predicate = lua_toboolean(L, 2);
		lua_settop(L, 1);
		self.predicates_ref = luaL_ref(L, LUA_REGISTRYINDEX);
		break;

	default:
		return luaL_error(L,
			"bad argument #1 (table or nil expected, got %s)",
			lua_typename(L, lua_type(L, 1))
		);
	}

	LTS_push_query_iterator(L, self);
	return 1;
}

static int LTS_query_iterator_delete(lua_State *L) {
	LTS_QueryIterator self = *LTS_log_gc(LTS_check_query_iterator(L, 1), LTS_QUERY_ITERATOR_METATABLE_NAME);
	
	luaL_unref(L, LUA_REGISTRYINDEX, self.predicates_ref);
	return 0;
}

static bool run_predicates(
	lua_State *L,
	LTS_Query query,
	TSQueryMatch match,
	int match_idx,
	int predicates_idx
) {
	uint32_t count;
	const TSQueryPredicateStep *steps = ts_query_predicates_for_pattern(
		query.query,
		match.pattern_index,
		&count
	);

	for (uint32_t i = 0; i < count; i++) {
		uint16_t arg_count = 0;
		uint32_t len;
		const char *name =
			ts_query_string_value_for_id(query.query, steps[i].value_id, &len);
		i++;

		if (lua_isnil(L, predicates_idx)) {
			while (steps[i].value_id != TSQueryPredicateStepTypeDone) i++;
			continue;
		} else {
			lua_pushlstring(L, name, len);
			lua_rawget(L, predicates_idx);
			if (lua_isnil(L, -1)) {
				while (steps[i].value_id != TSQueryPredicateStepTypeDone) i++;
				lua_pop(L, 1);
				continue;
			}
		}

		for (; i < count; i++) {
			TSQueryPredicateStep step = steps[i];
			switch (step.type) {
			case TSQueryPredicateStepTypeCapture:
				LTS_push_query_capture_spec(L, step.value_id, match_idx);
				break;

			case TSQueryPredicateStepTypeString:
				LTS_push_query_string_value_for_id(query, step.value_id);
				break;

			case TSQueryPredicateStepTypeDone:
				goto do_func;
			}

			arg_count++;
		}

	do_func:
		if (lua_pcall(L, arg_count, 1, 0) != 0) {
			return luaL_error(L,
				"error while executing predicate '#%s': %s",
				name, lua_tostring(L, -1)
			);
		}

		if (name[len - 1] == '?') {
			bool ok = lua_toboolean(L, -1);
			lua_pop(L, 1);
			if (!ok) return false;
		} else {
			lua_pop(L, 1);
		}
	}

	return true;
}

static int next_match(lua_State *L) {
	LTS_QueryCursor cursor = *(LTS_QueryCursor *) lua_touserdata(L, lua_upvalueindex(1));

	TSQueryMatch match;
	do {
		lua_settop(L, 0);

		bool ok = ts_query_cursor_next_match(cursor.query_cursor, &match);
		if (!ok) {
			lua_pushnil(L);
			return 1;
		}

		LTS_push_query_match(L, match, lua_upvalueindex(1));
	} while (!run_predicates(L, *cursor.query, match, 1, lua_upvalueindex(2)));

	return 1;
}

static int LTS_query_iterator_matches(lua_State *L) {
	LTS_QueryIterator self = *LTS_check_query_iterator(L, 1);
	luaL_checkudata(L, 2, LTS_QUERY_CURSOR_METATABLE_NAME);

	lua_settop(L, 2);
	lua_rawgeti(L, LUA_REGISTRYINDEX, self.predicates_ref);

	lua_pushcclosure(L, next_match, 2);
	return 1;
}

static int next_capture(lua_State *L) {
	LTS_QueryCursor cursor = *(LTS_QueryCursor *) lua_touserdata(L, lua_upvalueindex(1));

	TSQueryMatch match;
	uint32_t index;
	do {
		lua_settop(L, 0);

		bool ok = ts_query_cursor_next_capture(cursor.query_cursor, &match, &index);
		if (!ok) {
			lua_pushnil(L);
			return 1;
		}

		LTS_push_query_match(L, match, lua_upvalueindex(1));
	} while (!run_predicates(L, *cursor.query, match, 1, lua_upvalueindex(2)));

	LTS_push_query_capture(L, match.captures[index], 1);
	return 1;
}

static int LTS_query_iterator_captures(lua_State *L) {
	LTS_QueryIterator self = *LTS_check_query_iterator(L, 1);
	luaL_checkudata(L, 2, LTS_QUERY_CURSOR_METATABLE_NAME);

	lua_settop(L, 2);
	lua_rawgeti(L, LUA_REGISTRYINDEX, self.predicates_ref);

	lua_pushcclosure(L, next_capture, 2);
	return 1;
}

static const luaL_Reg methods[] = {
	{ "matches", LTS_query_iterator_matches },
	{ "captures", LTS_query_iterator_captures },
	{ NULL, NULL }
};

static const luaL_Reg metamethods[] = {
	{ "__gc", LTS_query_iterator_delete },
	{ NULL, NULL }
};

static const luaL_Reg funcs[] = {
	{ "new", LTS_query_iterator_new },
	{ NULL, NULL }
};

void LTS_setup_query_iterator(lua_State *L) {
	LTS_util_make_metatable(L, LTS_QUERY_ITERATOR_METATABLE_NAME, methods, metamethods);
	LTS_util_make_functable(L, LTS_QUERY_ITERATOR_FUNCTABLE_NAME, funcs);
}
