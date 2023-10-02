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
-- @treturn Node
function Node:tree() end

---
-- Metamethods
-- @section Metamethods

---
-- Check equality of two nodes by value.
-- @tparam Node other
-- @treturn bool
function Node:__eq(other) end

---
-- Convert the node to a S-expression.
-- @treturn string
function Node:__tostring() end
