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
				'src/init.c',
				'src/language.c',
				'src/node.c',
				'src/parser.c',
				'src/point.c',
				'src/query.c',
				'src/query_capture.c',
				'src/query_capture_spec.c',
				'src/query_cursor.c',
				'src/query_iterator.c',
				'src/query_match.c',
				'src/range.c',
				'src/range_array.c',
				'src/tree.c',
				'src/util.c',
			},
		},
	},
	copy_directories = {
	},
}
