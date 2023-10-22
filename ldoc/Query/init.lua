---
-- A query that can be ran on `Node`s of a given `Language`.
-- Analogous to `TSQuery`.
-- @classmod Query
-- @pragma nostrip

---
-- Functions
-- @section Functions


---
-- Create a new query for a given `Language` from a source `string`.
-- @tparam Language lang
-- @tparam string source
-- @treturn Query
-- @raise Invalid pattern in the source.
function Query.new(lang, source) end

---
-- Methods
-- @section Methods

