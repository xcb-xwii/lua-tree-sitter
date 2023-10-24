---
-- A set of `Capture`s provided to predicates.
-- @classmod Query.CaptureSet
-- @pragma nostrip

---
-- Methods
-- @section Methods

---
-- Get the index of the captures.
-- @treturn integer
function CaptureSet:index() end

---
-- Get the `QueryMatch` the captures belongs to.
-- @treturn Match
function CaptureSet:match() end

---
-- Get the name of the captures.
-- @treturn string
function CaptureSet:name() end

---
-- Get the quantifier of the captures.
--
-- The quantifier can be one of 5 values:
--
-- 1. "Zero"
--
-- 2. "ZeroOrOne"
--
-- 3. "One"
--
-- 4. "ZeroOrMore"
--
-- 5. "OneOrMore"
-- @treturn string
function CaptureSet:quantifier() end

---
-- Get one capture.
--
-- This is useful when there are only 0 or 1 captures in the set.
--
-- If you only need the node, which is the usual use-case, use `one_node`
-- instead.
-- @treturn Capture|nil
function CaptureSet:one_capture() end

---
-- Get one node.
--
-- This is useful when there are only 0 or 1 captures in the set.
-- @treturn Node|nil
function CaptureSet:one_node() end

---
-- Get all the captures in the set in a table.
--
-- If you only need the nodes, which is the usual use-case, use
-- `nodes_to_table` instead.
-- @treturn {Capture}
function CaptureSet:captures_to_table() end

---
-- Get all the nodes in the set in a table.
-- @treturn {Node}
function CaptureSet:nodes_to_table() end
