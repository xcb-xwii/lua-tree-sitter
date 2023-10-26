---
-- A quantified set of `Query.Capture`s provided to predicates.
-- @classmod Query.QuantifiedCapture
-- @pragma nostrip

---
-- Methods
-- @section Methods

---
-- Get the index of the captures.
-- @treturn integer
function QuantifiedCapture:index() end

---
-- Get the `QueryMatch` the captures belongs to.
-- @treturn Match
function QuantifiedCapture:match() end

---
-- Get the name of the captures.
-- @treturn string
function QuantifiedCapture:name() end

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
function QuantifiedCapture:quantifier() end

---
-- Get one capture.
--
-- This is useful when there are only 0 or 1 captures in the set.
--
-- If you only need the node, which is the usual use-case, use `one_node`
-- instead.
-- @treturn Capture|nil
function QuantifiedCapture:one_capture() end

---
-- Get one node.
--
-- This is useful when there are only 0 or 1 captures in the set.
-- @treturn Node|nil
function QuantifiedCapture:one_node() end

---
-- Get all the captures in the set in a table.
--
-- If you only need the nodes, which is the usual use-case, use
-- `nodes` instead.
-- @treturn {Capture}
function QuantifiedCapture:captures() end

---
-- Get all the nodes in the set in a table.
-- @treturn {Node}
function QuantifiedCapture:nodes() end
