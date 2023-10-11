---
-- A cursor for executing a given `Query`.
-- Analogous to `TSQueryCursor`.
-- @classmod QueryCursor
-- @pragma nostrip

---
-- Functions
-- @section Functions

---
-- Create a new cursor for executing a given `Query` on a given `Node`.
-- @tparam Query query
-- @tparam Node node
-- @treturn QueryCursor
function QueryCursor.new(query, node) end

---
-- Methods
-- @section Methods

---
-- Get the `Query` the cursor is executing.
-- @treturn Query
function QueryCursor:query() end

---
-- Set the range of `Point`s in which the `Query` will be executed.
-- @tparam Point start_point
-- @tparam Point end_point
function QueryCursor:set_point_range(start_point, end_point) end

---
-- Advance to and get the next match.
--
-- This method may return `nil` if there are no more matches.
-- @treturn QueryMatch|nil
function QueryCursor:next_match() end

---
-- Advance to and get the next capture.
--
-- This method may return `nil` if there are no more captures.
-- @treturn QueryCapture|nil
function QueryCursor:next_capture() end
