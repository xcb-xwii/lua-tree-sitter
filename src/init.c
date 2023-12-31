#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include <lts/language.h>
#include <lts/node.h>
#include <lts/parser.h>
#include <lts/point.h>
#include <lts/query/init.h>
#include <lts/query/capture.h>
#include <lts/query/quantified_capture.h>
#include <lts/query/cursor.h>
#include <lts/query/match.h>
#include <lts/query/runner.h>
#include <lts/range/init.h>
#include <lts/range/array.h>
#include <lts/tree.h>
#include <lts/util.h>

LTS_EXPORT int luaopen_lua_tree_sitter(lua_State *L) {
	lua_createtable(L, 0, 0);

	LTS_setup_language(L);
	LTS_setup_node(L);
	LTS_setup_parser(L);
	LTS_setup_point(L);
	LTS_setup_query(L);

	lua_getfield(L, -1, "Query");
	LTS_setup_query_capture(L);
	LTS_setup_query_quantified_capture(L);
	LTS_setup_query_cursor(L);
	LTS_setup_query_match(L);
	LTS_setup_query_runner(L);
	lua_pop(L, 1);

	LTS_setup_range(L);
	lua_getfield(L, -1, "Range");
	LTS_setup_range_array(L);
	lua_pop(L, 1);

	LTS_setup_tree(L);

	return 1;
}
