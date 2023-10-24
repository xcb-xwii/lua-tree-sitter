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
			incdirs = { '$(TREE_SITTER_INCDIR)', 'include' },
			libraries = { 'tree-sitter' },
			sources = {
				'src/init.c',
				'src/language.c',
				'src/node.c',
				'src/parser.c',
				'src/point.c',
				'src/query/init.c',
				'src/query/capture.c',
				'src/query/capture_set.c',
				'src/query/cursor.c',
				'src/query/match.c',
				'src/query/runner.c',
				'src/range/init.c',
				'src/range/array.c',
				'src/tree.c',
				'src/util.c',
			},
		},
	},
	copy_directories = {
	},
}
