---
-- A array of `Range`s.
-- Used for efficient handling of such arrays.
-- @classmod Ranges
-- @pragma nostrip

---
-- Functions
-- @section Functions

---
-- Create a new array.
--
-- If you do not already have a Lua `table` of the ranges, consider using `pack`.
-- @tparam {Range} array
-- @treturn Ranges
function Ranges.new(array) end

---
-- Create a new array from a variable number of arguments.
-- @tparam Range ...
-- @treturn Ranges
function Ranges.pack(...) end

---
-- Alias for `new`.
-- @tparam {Range} array
-- @treturn Ranges
function Ranges.from_table(array) end

---
-- Methods
-- @section Methods

---
-- Unpack the array.
--
-- Inverse of `pack` if `i` and `j` are omitted.
-- @tparam[opt=1] integer i
-- @tparam[opt=length of array] integer j last index to unpack (inclusive)
-- @treturn Range...
function Ranges:unpack(i, j) end

---
-- Convert the array to a Lua `table`.
--
-- Inverse of `from_table`.
-- @treturn {Ranges}
function Ranges:to_table() end

---
-- Create a copy of the array.
-- @treturn Ranges
function Ranges:copy() end

---
-- Get the `Range` at a given index.
-- @tparam integer index
-- @treturn Range
-- @raise Indexing a non-positive index.  
-- Indexing beyond last element.
function Ranges:at(index) end

---
-- Set the `Range` at a given index.
-- @tparam integer index
-- @tparam Range value
-- @raise Indexing a non-positive index.  
-- Indexing beyond last element.  
-- Mutating an unmanaged array.
function Ranges:set_at(index, value) end

---
-- Metamethods
-- @section Metamethods

---
-- Get the length of the array.
-- @treturn integer
function Ranges:__len() end

---
-- Check equality of two arrays.
-- @tparam Ranges other
-- @treturn boolean
function Ranges:__eq(other) end
