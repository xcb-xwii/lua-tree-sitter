---
-- A range within a document.
-- Analogous to `TSRange`.
-- @classmod Range
-- @pragma nostrip

---
-- Functions
-- @section Functions

---
-- Create a new range.
-- @tparam Point start_point
-- @tparam Point end_point
-- @tparam integer start_byte
-- @tparam integer end_byte
-- @treturn Range
function Range.new(start_point, end_point, start_byte, end_byte) end

---
-- Alias for `new`.
-- @tparam Point start_point
-- @tparam Point end_point
-- @tparam integer start_byte
-- @tparam integer end_byte
-- @treturn Range
function Range.pack(start_point, end_point, start_byte, end_byte) end

---
-- Methods
-- @section Methods

---
-- Unpack the range.
--
-- Inverse of `pack`.
-- @treturn Point start point
-- @treturn Point end point
-- @treturn integer start byte
-- @treturn integer end byte
function Range:unpack() end

---
-- Get the start point of the range.
-- @treturn Point
function Range:start_point() end

---
-- Get the end point of the point.
-- @treturn integer
function Range:end_point() end

---
-- Get the start byte of the range.
-- @treturn Point
function Range:start_byte() end

---
-- Get the end byte of the point.
-- @treturn integer
function Range:end_byte() end

---
-- Metamethods
-- @section Metamethods

---
-- Check equality of two ranges by value.
-- @tparam Range other
-- @treturn boolean
function Range:__eq(other) end
