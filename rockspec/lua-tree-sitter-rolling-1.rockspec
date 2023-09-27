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
		['tree_sitter'] = 'lua/init.lua',
		['tree_sitter.language'] = 'lua/language.lua',
		['tree_sitter.node'] = 'lua/node.lua',
		['tree_sitter.parser'] = 'lua/parser.lua',
		['tree_sitter.point'] = 'lua/point.lua',
		['tree_sitter.tree'] = 'lua/tree.lua',
		['lua_tree_sitter'] = {
			libdirs = { '$(TREE_SITTER_LIBDIR)' },
			incdirs = { '$(TREE_SITTER_INCDIR)' },
			libraries = { 'tree-sitter' },
			sources = {
				'c/tree_sitter.c',
				'c/input.c',
				'c/language.c',
				'c/node.c',
				'c/parser.c',
				'c/point.c',
				'c/tree.c',
				'c/util.c',
			},
		},
	},
	copy_directories = {
	},
}
