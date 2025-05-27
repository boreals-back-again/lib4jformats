# Tests

lib4jformats uses Catch2 for tests. The files required for testing are binary, and quite large. This is why they are in a [separate repository](https://github.com/boreals-back-again/l4jf-tests-files). Catch2 and json are acquired using `FetchContent` in CMake, so you don't need to worry about supplying these yourself.


## LOC Tests
- "Parse and write LOC"\
Open LOC file, copy to stringstream, re-serialize with LOCFile, and compare output.
- "Convert between LOC and JSON"\
Parse LOC file, convert to JSON and back, then assert equivalence with original.
