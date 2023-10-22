---
-- A cursor for executing a given `Query`.
-- Analogous to `TSQueryCursor`.
-- @classmod Query.Cursor
-- @pragma nostrip

---
-- Functions
-- @section Functions

---
-- Create a new cursor for executing a given `Query` on a given `Node`.
-- @tparam Query query
-- @tparam Node node
-- @treturn Cursor
function Cursor.new(query, node) end

---
-- Methods
-- @section Methods

---
-- Get the `Query` the cursor is executing.
-- @treturn Query
function Cursor:query() end

---
-- Get the `Node` the cursor is executing on.
-- @treturn Node
function Cursor:node() end

---
-- Check whether the match limit of the cursor has been exceeded.
-- @treturn boolean
function Cursor:did_exceed_match_limit() end

---
-- Get the maximum number of in-progress matches of a cursor.
--
-- If the maximum number is reached, the earliest match is silently dropped.
--
-- By default, there is no maximum.
-- @treturn integer
function Cursor:match_limit() end

---
-- Set the maximum number of in-progress matches of a cursor.
-- @tparam integer limit
function Cursor:set_match_limit(limit) end

---
-- Set the range of bytes in which the `Query` will be executed.
-- @tparam integer start_byte
-- @tparam integer end_byte
function Cursor:set_byte_range(start_byte, end_byte) end

---
-- Set the range of `Point`s in which the `Query` will be executed.
-- @tparam Point start_point
-- @tparam Point end_point
function Cursor:set_point_range(start_point, end_point) end

---
-- Advance to and get the next match.
--
-- This method may return `nil` if there are no more matches.
-- @treturn Match|nil
function Cursor:next_match() end

---
-- Advance to and get the next capture.
--
-- This method may return `nil` if there are no more captures.
-- @treturn Capture|nil
function Cursor:next_capture() end
