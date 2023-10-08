---
-- A array of `Range`s.
-- Used for efficient handling of such arrays.
-- @classmod RangeArray
-- @pragma nostrip

---
-- Functions
-- @section Functions

---
-- Create a new array.
--
-- If you do not already have a Lua `table` of the `Range`s, consider using `pack`.
-- @tparam {Range} array
-- @treturn RangeArray
function RangeArray.new(array) end

---
-- Create a new array from a variable number of arguments.
-- @tparam Range ...
-- @treturn RangeArray
function RangeArray.pack(...) end

---
-- Alias for `new`.
-- @tparam {Range} array
-- @treturn RangeArray
function RangeArray.from_table(array) end

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
function RangeArray:unpack(i, j) end

---
-- Convert the array to a Lua `table`.
--
-- Inverse of `from_table`.
-- @treturn {RangeArray}
function RangeArray:to_table() end

---
-- Create a copy of the array.
-- @treturn RangeArray
function RangeArray:copy() end

---
-- Get the `Range` at a given index.
-- @tparam integer index
-- @treturn Range
-- @raise Indexing a non-positive index.  
-- Indexing beyond last element.
function RangeArray:at(index) end

---
-- Set the `Range` at a given index.
-- @tparam integer index
-- @tparam Range value
-- @raise Indexing a non-positive index.  
-- Indexing beyond last element.  
-- Mutating an unmanaged array.
function RangeArray:set_at(index, value) end

---
-- Metamethods
-- @section Metamethods

---
-- Get the length of the array.
-- @treturn integer
function RangeArray:__len() end

---
-- Check equality of two arrays.
-- @tparam RangeArray other
-- @treturn boolean
function RangeArray:__eq(other) end
