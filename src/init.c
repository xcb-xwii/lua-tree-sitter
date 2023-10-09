#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include "language.h"
#include "node.h"
#include "parser.h"
#include "point.h"
#include "query.h"
#include "query_capture.h"
#include "query_capture_spec.h"
#include "query_cursor.h"
#include "query_iterator.h"
#include "query_match.h"
#include "range.h"
#include "range_array.h"
#include "tree.h"
#include "util.h"

int luaopen_tree_sitter(lua_State *L) {
	lua_createtable(L, 0, 0);
	LTS_setup_language(L);
	LTS_setup_node(L);
	LTS_setup_parser(L);
	LTS_setup_point(L);
	LTS_setup_query(L);
	LTS_setup_query_capture(L);
	LTS_setup_query_capture_spec(L);
	LTS_setup_query_cursor(L);
	LTS_setup_query_iterator(L);
	LTS_setup_query_match(L);
	LTS_setup_range(L);
	LTS_setup_range_array(L);
	LTS_setup_tree(L);

	return 1;
}
