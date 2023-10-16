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
function Language.load(path, name) end

---
-- Require a language from a dynamic library.
--
-- Searches `cpath` for a parser that matches `name`.
-- If `cpath` is not provided, `package.cpath` is used.
--
-- '`?`'s in the paths are replaced by `name` when searching for the dynamic
-- library.
-- @tparam string name name of the language
-- @tparam ?string cpath paths to search for the library
-- @treturn Language language definition
function Language.require(name, cpath) end

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
-- @treturn boolean
function Language:__eq(other) end
