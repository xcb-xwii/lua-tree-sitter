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
-- Get the `Node` the cursor is executing on.
-- @treturn Node
function QueryCursor:node() end

---
-- Check whether the match limit of the cursor has been exceeded.
-- @treturn boolean
function QueryCursor:did_exceed_match_limit() end

---
-- Get the maximum number of in-progress matches of a cursor.
--
-- If the maximum number is reached, the earliest match is silently dropped.
--
-- By default, there is no maximum.
-- @treturn integer
function QueryCursor:match_limit() end

---
-- Set the maximum number of in-progress matches of a cursor.
-- @tparam integer limit
function QueryCursor:set_match_limit(limit) end

---
-- Set the range of bytes in which the `Query` will be executed.
-- @tparam integer start_byte
-- @tparam integer end_byte
function QueryCursor:set_byte_range(start_byte, end_byte) end

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
