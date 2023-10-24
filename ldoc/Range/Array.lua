---
-- A array of `Range`s.
-- Used for efficient handling of such arrays.
-- @classmod Range.Array
-- @pragma nostrip

---
-- Functions
-- @section Functions

---
-- Create a new array.
--
-- If you do not already have a Lua `table` of the `Range`s, consider using `pack`.
-- @tparam {Range} array
-- @treturn Array
function Array.new(array) end

---
-- Create a new array from a variable number of arguments.
-- @tparam Range ...
-- @treturn Array
function Array.pack(...) end

---
-- Alias for `new`.
-- @tparam {Range} array
-- @treturn Array
function Array.from_table(array) end

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
function Array:unpack(i, j) end

---
-- Convert the array to a Lua `table`.
--
-- Inverse of `from_table`.
-- @treturn {Array}
function Array:to_table() end

---
-- Create a copy of the array.
-- @treturn Array
function Array:copy() end

---
-- Get the `Range` at a given index.
-- @tparam integer index
-- @treturn Range
-- @raise Indexing a non-positive index.  
-- Indexing beyond last element.
function Array:at(index) end

---
-- Set the `Range` at a given index.
-- @tparam integer index
-- @tparam Range value
-- @raise Indexing a non-positive index.  
-- Indexing beyond last element.  
-- Mutating an unmanaged array.
function Array:set_at(index, value) end

---
-- Metamethods
-- @section Metamethods

---
-- Get the length of the array.
-- @treturn integer
function Array:__len() end

---
-- Check equality of two arrays.
-- @tparam Array other
-- @treturn boolean
function Array:__eq(other) end
