---
-- A capture of a `Query`.
-- Analogous to `TSQueryCapture`.
-- @classmod Query.Capture
-- @pragma nostrip

---
-- Methods
-- @section Methods

---
-- Get the `Node` of the capture.
-- @treturn Node
function Capture:node() end

---
-- Get the index of the capture.
-- @treturn integer
function Capture:index() end

---
-- Get the `QueryMatch` the capture belongs to.
-- @treturn Match
function Capture:match() end

---
-- Get the `Query` the capture belongs to.
-- @treturn Query
function Capture:query() end

---
-- Get the name of the capture.
-- @treturn Node
function Capture:name() end
