---
-- A language definition used by a `Parser` to parse a document.
-- Analogous to `TSLanguage`.
-- @classmod Language
-- @pragma nostrip

---
-- Functions
-- @section Functions

---
-- Load a language from a dynamic library.
-- @tparam string path path to the dynamic library
-- @tparam string name name of the language
-- @treturn Language language definition
function Language.new(path, name) end

---
-- Methods
-- @section Methods

---
-- Get the ABI version number for this language.
-- @treturn integer version
function Language:version() end

---
-- Metamethods
-- @section Metamethods

---
-- Check equality of two languages.
-- @tparam Language other
-- @treturn bool
function Language:__eq(other) end
