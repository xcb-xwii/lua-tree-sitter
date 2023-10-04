rockspec_format = '3.0'

package = 'lua-tree-sitter'
version = 'rolling-1'

description = {
	summary = 'Lua bindings for Tree-sitter',
	detailed = 'Lua bindings for Tree-sitter',
	license = 'MIT',
	homepage = 'https://github.com/xcb-xwii/lua-tree-sitter',
	issues_url = 'https://github.com/xcb-xwii/lua-tree-sitter/issues',
	-- maintainer = '',
	-- labels = '',
}

external_dependencies = {
	TREE_SITTER = {
		header = 'tree_sitter/api.h',
	},
}

source = {
	url = 'git+https://github.com/xcb-xwii/lua-tree-sitter'
}

build = {
	type = 'builtin',
	modules = {
		['tree_sitter'] = {
			libdirs = { '$(TREE_SITTER_LIBDIR)' },
			incdirs = { '$(TREE_SITTER_INCDIR)' },
			libraries = { 'tree-sitter' },
			sources = {
				'c/init.c',
				'c/language.c',
				'c/node.c',
				'c/parser.c',
				'c/point.c',
				'c/query.c',
				'c/query_capture.c',
				'c/query_cursor.c',
				'c/query_iterator.c',
				'c/query_match.c',
				'c/range.c',
				'c/ranges.c',
				'c/tree.c',
				'c/util.c',
			},
		},
	},
	copy_directories = {
	},
}
