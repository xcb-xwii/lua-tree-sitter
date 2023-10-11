---
-- A capture of a `Query`.
-- Analogous to `TSQueryCapture`.
-- @classmod QueryCapture
-- @pragma nostrip

---
-- Methods
-- @section Methods

---
-- Get the `Node` of the capture.
-- @treturn Node
function QueryCapture:node() end

---
-- Get the index of the capture.
-- @treturn integer
function QueryCapture:index() end

---
-- Get the `QueryMatch` the capture belongs to.
-- @treturn QueryMatch
function QueryCapture:match() end

---
-- Get the `Query` the capture belongs to.
-- @treturn Query
function QueryCapture:query() end

---
-- Get the name of the capture.
-- @treturn Node
function QueryCapture:name() end
