# Tests

lib4jformats uses Catch2 for tests. The files required for testing are binary, and quite large. This is why they are in a [separate repository](https://github.com/boreals-back-again/l4jf-tests-files). Catch2 and json are acquired using `FetchContent` in CMake, so you don't need to worry about supplying these yourself.

## LOC Test
- "LOC <--> JSON"
Opens a LOC file as an `fstream`, converts it to a JSON object, and asserts the new LOC created from the JSON object is the same as the original.
