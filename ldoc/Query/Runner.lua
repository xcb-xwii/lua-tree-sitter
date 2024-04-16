---
-- Runs `Query`s with support for predicates.
-- @classmod Query.Runner
-- @pragma nostrip

---
-- Functions
-- @section Functions

---
-- Create a new runner with a given set of predicates.
--
-- Predicates are functions that take a variable number of parameters of type
-- `QuantifiedCapture` or `string`.
--
-- Currently, predicates' return values are ignored and discarded, unless the
-- name of the predicate ends with '`?`'. In this case, falsey values
-- short-circuit the execution of further predicates and causes the
-- corresponding `Match` or `Capture` to be skipped.
--
-- If results of predicates need to be saved, it is recommended to use closures
-- with side-effects for these predicates.
--
-- The `setup` function is ran before executing the predicates of a `Match` or
-- `Capture`. This may be useful to ensure side-effects of skipped items are
-- erased.
-- @tparam {string:function(...)} predicates
-- @tparam ?function() setup
-- @treturn Runner
function Runner.new(predicates, setup) end

---
-- Methods
-- @section Methods

---
-- Iterate over the `Match`es of a cursor, executing predicates.
--
-- @tparam Cursor cursor
-- @treturn function():Match iterator
function Runner:iter_matches(cursor) end

---
-- Uterate over the `Capture`s of a cursor, executing predicates.
--
-- @tparam cursor cursor
-- @treturn function():Capture iterator
function Runner:iter_captures(cursor) end
