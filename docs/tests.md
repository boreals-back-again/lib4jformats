# Tests
lib4jformats has unit tests for each file type. In order to test, sample files are required. These are quite large, so they are cloned from [another repository](https://github.com/boreals-back-again/l4jf-tests-files). 

doctest is used for testing. Both doctest and json are supplied with `FetchContent`, so you don't need to worry about supplying them yourself.

## ARC Tests
1. **"Parse and write ARC"** Open ARC file, copy to stringstream, re-serialize with ARCFile, and compare output.

## LOC Tests
1. **"Parse and write LOC"** Open LOC file, copy to stringstream, re-serialize with LOCFile, and compare output.
2. **"Convert between LOC and JSON"** Parse LOC file, convert to JSON and back, then assert equivalence with original.
3. **"Getting and setting LOC entries** Open LOC File, Get a string by its ID, check it's the correct one, set the same string by it's ID, and check that the string was set
