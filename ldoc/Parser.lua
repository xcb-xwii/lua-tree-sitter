---
-- Parses a document based on a `Language` to produce a `Tree`.
-- Analogous to `TSParser`.
-- @classmod Parser
-- @pragma nostrip

---
-- Functions
-- @section Functions

---
-- Create a new parser.
-- @treturn Parser
function Parser.new() end

---
-- Methods
-- @section Methods

---
-- Get the parser's current language.
-- @treturn Language
function Parser:language() end

---
-- Set the language that the parser should use for parsing.
-- @tparam Language lang
function Parser:set_language(lang) end

---
-- Use the parser to parse some source code and create a syntax tree.
--
-- If you are parsing this document for the first time, pass `nil` for the
-- `old_tree` parameter.
--
-- Otherwise, pass the previous syntax tree for the `old_tree` parameter.
-- For this to work correctly, you must have already edited the old syntax tree
-- using `Tree:edit` so that it matches the source code changes.
--
-- The reader function takes a byte offset and a `Point`,
-- and returns a a chunk of text that starts at the point given.
-- Return an empty `string` or `nil` to signal end of the document.
--
-- If your reader function has to take the substring of a larger string,
-- consider using `parse_`.
-- @tparam Tree old_tree edited syntax tree
-- @tparam function(integer,Point):string read reader function
-- @treturn Tree
function Parser:parse(old_tree, read) end

---
-- Like `Parser.parse`, but the reader function returns a second `integer`
-- value representing the offset at which the requested chunk of text starts
-- within the string.
--
-- This is provided so you can avoid having to create substrings, improving
-- performance.
-- @tparam Tree old_tree edited syntax tree
-- @tparam function(integer,Point):string,integer read reader function
-- @treturn Tree
function Parser:parse_(old_tree, read) end
