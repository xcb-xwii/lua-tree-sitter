---
-- A node within a `Tree`.
-- Analogous to `TSNode`.
-- @classmod Node
-- @pragma nostrip

---
-- Methods
-- @section Methods

---
-- Get the `Tree` the node belongs to.
-- @treturn Tree
function Node:tree() end

---
-- Get the type of the node.
-- @treturn string
function Node:type() end

---
-- Get the start byte of the node.
-- @treturn integer
function Node:start_byte() end

---
-- Get the start `Point` of the node.
-- @treturn Point
function Node:start_point() end

---
-- Get the end byte of the node.
-- @treturn integer
function Node:end_byte() end

---
-- Get the end `Point` of the node.
-- @treturn Point
function Node:end_point() end

---
-- Check if the node is named.
-- @treturn boolean
function Node:is_named() end

---
-- Check if the node is missing.
-- @treturn boolean
function Node:is_missing() end

---
-- Check if the node is extra.
-- @treturn boolean
function Node:is_extra() end

---
-- Check if the node has been edited.
-- @treturn boolean
function Node:has_changes() end

---
-- Check if the node is a syntax error or contains any syntax errors.
-- @treturn boolean
function Node:has_error() end

---
-- Get the immediate parent of the node.
--
-- This method may return `nil` if no such node exists.
-- @treturn Node|nil
function Node:parent() end

---
-- Get the child of the node at a given index.
--
-- This method may return `nil` if no such node exists.
-- @tparam integer index
-- @treturn Node|nil
function Node:child(index) end

---
-- Get the field name of the child of the node at a given index.
--
-- This method may return `nil` if the node has no field name.
-- @tparam integer index
-- @treturn string|nil
function Node:field_name_for_child(index) end

---
-- Get the number of children the node has.
-- @treturn integer
function Node:child_count() end

---
-- Get the named child of the node at a given index.
--
-- This method may return `nil` if no such node exists.
-- @tparam integer index
-- @treturn Node|nil
function Node:named_child(index) end

---
-- Get the number of named children the node has.
-- @treturn integer
function Node:named_child_count() end

---
-- Get the child of the node by a given field ID.
--
-- This method may return `nil` if no such node exists.
-- @tparam integer id
-- @treturn Node|nil
function Node:child_by_field_id(id) end

---
-- Get the next sibling of the node.
--
-- This method may return `nil` if no such node exists.
-- @treturn Node|nil
function Node:next_sibling() end

---
-- Get the previous sibling of the node.
--
-- This method may return `nil` if no such node exists.
-- @treturn Node|nil
function Node:prev_sibling() end

---
-- Get the next named sibling of the node.
--
-- This method may return `nil` if no such node exists.
-- @treturn Node|nil
function Node:next_named_sibling() end

---
-- Get the previous named_sibling of the node.
--
-- This method may return `nil` if no such node exists.
-- @treturn Node|nil
function Node:prev_named_sibling() end

---
-- Get the first child of the node that extends beyond the given byte offset.
--
-- This method may return `nil` if no such node exists.
-- @tparam integer byte
-- @treturn Node|nil
function Node:first_child_for_byte(byte) end

---
-- Get the first named child of the node that extends beyond the given byte offset.
--
-- This method may return `nil` if no such node exists.
-- @tparam integer byte
-- @treturn Node|nil
function Node:first_named_child_for_byte(byte) end

---
-- Get the smallest node within the node that spans the given range of bytes.
--
-- This method may return `nil` if no such node exists.
-- @tparam integer start_byte
-- @tparam integer end_byte
-- @treturn Node|nil
function Node:descendant_for_byte_range(start_byte, end_byte) end

---
-- Get the smallest node within the node that spans the given range of `Point`s.
--
-- This method may return `nil` if no such node exists.
-- @tparam integer start_point
-- @tparam integer end_point
-- @treturn Node|nil
function Node:descendant_for_point_range(start_point, end_point) end

---
-- Get the smallest named node within the node that spans the given range of bytes.
--
-- This method may return `nil` if no such node exists.
-- @tparam integer start_byte
-- @tparam integer end_byte
-- @treturn Node|nil
function Node:named_descendant_for_byte_range(start_byte, end_byte) end

---
-- Get the smallest named node within the node that spans the given range of `Point`s.
--
-- This method may return `nil` if no such node exists.
-- @tparam integer start_point
-- @tparam integer end_point
-- @treturn Node|nil
function Node:named_descendant_for_point_range(start_point, end_point) end

---
-- Metamethods
-- @section Metamethods

---
-- Check equality of two nodes by value.
-- @tparam Node other
-- @treturn boolean
function Node:__eq(other) end

---
-- Convert the node to a S-expression.
-- @treturn string
function Node:__tostring() end
