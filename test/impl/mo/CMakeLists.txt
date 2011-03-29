add_library(MOCoreTest
  ClangInstanceTest.cpp
  SmellFinderTest.cpp
  RuleDataTest.cpp
  RuleSetTest.cpp
  TraverseASTTest.cpp
  )

add_subdirectory(exception)
add_subdirectory(reporter)
add_subdirectory(rule)
add_subdirectory(util)
