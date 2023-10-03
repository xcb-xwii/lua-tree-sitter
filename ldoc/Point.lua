---
-- A point on a document.
-- Analogous to `TSPoint`.
-- @classmod Point
-- @pragma nostrip

---
-- Functions
-- @section Functions

---
-- Create a new point.
-- @tparam integer row
-- @tparam integer column
-- @treturn Point
function Point.new(row, column) end

---
-- Alias for `new`.
-- @tparam integer row
-- @tparam integer column
-- @treturn Point
function Point.pack(row, column) end

---
-- Methods
-- @section Methods

---
-- Unpack the point.
--
-- Inverse of `pack`.
-- @treturn integer row
-- @treturn integer column
function Point:unpack() end

---
-- Get the row of the point.
-- @treturn integer
function Point:row() end

---
-- Get the column of the point.
-- @treturn integer
function Point:column() end

---
-- Metamethods
-- @section Metamethods

---
-- Check equality of two points by value.
-- @tparam Point other
-- @treturn boolean
function Point:__eq(other) end

---
-- Check if a point occurs before another point.
-- @tparam Point other
-- @treturn boolean
function Point:__lt(other) end

---
-- Check if a point occurs before or is the same as another point.
-- @tparam Point other
-- @treturn boolean
function Point:__le(other) end
