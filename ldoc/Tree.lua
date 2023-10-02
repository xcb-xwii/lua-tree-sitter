---
-- A syntax tree.
-- Analogous to `TSTree`.
-- @classmod Tree
-- @pragma nostrip

---
-- Methods
-- @section Methods

---
-- Create a shallow copy of the syntax tree.
--
-- You need to copy a syntax tree in order to use it on more than one thread at
-- a time, as syntax trees are not thread safe.
-- @treturn Tree
function Tree:copy() end

---
-- Get the root node of the syntax tree.
-- @treturn Node
function Tree:root_node() end

---
-- Get the language that was used to parse the syntax tree.
-- @treturn Language
-- @see Parser:set_language
function Tree:language() end

---
-- Get the array of included ranges that was used to parse the syntax tree.
-- @treturn RangeArray
-- @see Parser:set_included_ranges
function Tree:included_ranges() end

---
-- Edit the syntax tree to keep it in sync with source code that has been
-- edited.
--
-- The edits have to be described in **both** byte offsets and `Point`s.
-- @tparam integer start_byte
-- @tparam integer old_end_byte
-- @tparam integer new_end_byte<br/>
-- @tparam Point start_point
-- @tparam Point old_end_point
-- @tparam Point new_end_point
function Tree:edit(
	start_byte, old_end_byte, new_end_byte,
	start_point, old_end_point, new_end_point
) end

---
-- Metamethods
-- @section Metamethods

---
-- Check equality of two trees by their root node.
--
-- Equivalent to calling `Node:__eq` on the two root nodes.
-- @tparam Tree other
-- @treturn bool
-- @see root_node
-- @see Node.__eq
function Tree:__eq(other) end
