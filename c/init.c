#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <tree_sitter/api.h>

#include "input.h"
#include "input_edit.h"
#include "language.h"
#include "node.h"
#include "parser.h"
#include "point.h"
#include "query.h"
#include "query_capture.h"
#include "query_cursor.h"
#include "query_match.h"
#include "range.h"
#include "ranges.h"
#include "tree.h"
#include "util.h"

int luaopen_tree_sitter(lua_State *L) {
	LTS_make_metatable_input(L);
	LTS_make_metatable_input_edit(L);
	LTS_make_metatable_language(L);
	LTS_make_metatable_node(L);
	LTS_make_metatable_parser(L);
	LTS_make_metatable_point(L);
	LTS_make_metatable_query(L);
	LTS_make_metatable_query_capture(L);
	LTS_make_metatable_query_cursor(L);
	LTS_make_metatable_query_match(L);
	LTS_make_metatable_range(L);
	LTS_make_metatable_ranges(L);
	LTS_make_metatable_tree(L);

	lua_createtable(L, 0, 0);
	LTS_make_functable_input(L);
	LTS_make_functable_input_edit(L);
	LTS_make_functable_language(L);
	LTS_make_functable_node(L);
	LTS_make_functable_parser(L);
	LTS_make_functable_point(L);
	LTS_make_functable_query(L);
	LTS_make_functable_query_capture(L);
	LTS_make_functable_query_cursor(L);
	LTS_make_functable_query_match(L);
	LTS_make_functable_range(L);
	LTS_make_functable_ranges(L);
	LTS_make_functable_tree(L);

	return 1;
}
