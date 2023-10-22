---
-- A match of a `Query`.
-- Analogous to `TSQueryMatch`.
-- @classmod Query.Match
-- @pragma nostrip

---
-- Methods
-- @section Methods

---
-- Get the pattern index of the match.
-- @treturn integer
function Match:pattern_index() end

---
-- Get the number of `QueryCapture`s in the match.
-- @treturn integer
function Match:capture_count() end

---
-- Get the `QueryCapture` at a given index.
-- @tparam integer index
-- @treturn Capture
-- @raise Indexing a negative index.  
-- Indexing beyond last element.
function Match:capture_at(index) end

---
-- Get the `Query` to which the match belongs.
-- @treturn Query
function Match:query() end
