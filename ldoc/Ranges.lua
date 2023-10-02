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
-- If you do not already have a Lua `table`, consider using `pack`.
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
-- Inverse of `pack`.
-- @treturn Range...
function Ranges:unpack() end

---
-- Convert the array to a Lua `table`.
--
-- Inverse of `from_table`.
-- @treturn {Ranges}
function Ranges:to_table() end

---
-- Check if this array is managed.
--
-- Only managed instances can be mutated.
-- If you need to mutate a non-managed instance, use `copy` and mutate the copy.
-- @treturn boolean
function Ranges:managed() end

---
-- Create a copy of the array.
-- @treturn Ranges
function Ranges:copy() end

---
-- Metamethods
-- @section Metamethods

---
-- Get the length of the array.
-- @treturn integer
function Ranges:__len() end

---
-- Get the `Range` at a given index.
-- @tparam integer index
-- @treturn Range
-- @raise Indexing a non-positive index.  
-- Indexing beyond last element.
function Ranges:__index(index) end

---
-- Set the `Range` at a given index.
-- @tparam integer index
-- @tparam Range value
-- @raise Indexing a non-positive index.  
-- Indexing beyond last element.  
-- Mutating an unmanaged array.
function Ranges:__newindex(index, value) end
