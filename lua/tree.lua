local lts = require 'lua_tree_sitter'

local M = {}
for name, func in pairs(lts.TSTree) do
	M[name] = func
end

return M
