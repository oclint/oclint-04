add_library(MOCore
  ClangInstance.cpp
  SmellFinder.cpp
  TraverseAST.cpp
  RuleViolation.cpp
  RuleData.cpp
  )

add_subdirectory(exception)
add_subdirectory(reporter)
add_subdirectory(rule)
add_subdirectory(util)
