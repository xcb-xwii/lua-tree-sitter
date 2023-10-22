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
#include <lts/query/capture_spec.h>
#include <lts/query/cursor.h>
#include <lts/query/iterator.h>
#include <lts/query/match.h>
#include <lts/range.h>
#include <lts/range_array.h>
#include <lts/tree.h>
#include <lts/util.h>

int luaopen_tree_sitter(lua_State *L) {
	lua_createtable(L, 0, 0);
	LTS_setup_language(L);
	LTS_setup_node(L);
	LTS_setup_parser(L);
	LTS_setup_point(L);
	LTS_setup_query(L);
	lua_getfield(L, -1, "Query");
	LTS_setup_query_capture(L);
	LTS_setup_query_capture_spec(L);
	LTS_setup_query_cursor(L);
	LTS_setup_query_iterator(L);
	LTS_setup_query_match(L);
	lua_pop(L, 1);
	LTS_setup_range(L);
	LTS_setup_range_array(L);
	LTS_setup_tree(L);

	return 1;
}
