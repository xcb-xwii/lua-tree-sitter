---
-- A match of a `Query`.
-- Analogous to `TSQueryMatch`.
-- @classmod QueryMatch
-- @pragma nostrip

---
-- Methods
-- @section Methods

---
-- Get the pattern index of the match.
-- @treturn integer
function QueryMatch:pattern_index() end

---
-- Get the number of `QueryCapture`s in the match.
-- @treturn integer
function QueryMatch:capture_count() end

---
-- Get the `QueryCapture` at a given index.
-- @tparam integer index
-- @treturn QueryCapture
-- @raise Indexing a negative index.  
-- Indexing beyond last element.
function QueryMatch:capture_at(index) end

---
-- Get the `Query` to which the match belongs.
-- @treturn Query
function QueryMatch:query() end
