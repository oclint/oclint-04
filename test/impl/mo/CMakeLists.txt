add_library(MOCoreTest
  ClangInstanceTest.cpp
  SmellFinderTest.cpp
  ViolationSetTest.cpp
  TraverseASTTest.cpp
  )

add_subdirectory(exception)
add_subdirectory(reporter)
add_subdirectory(rule)
add_subdirectory(ruleset)
add_subdirectory(util)
