add_library(MOCore
  ClangInstance.cpp
  SmellFinder.cpp
  TraverseAST.cpp
  Violation.cpp
  ViolationSet.cpp
  )

add_subdirectory(exception)
add_subdirectory(reporter)
add_subdirectory(rule)
add_subdirectory(ruleset)
add_subdirectory(util)
