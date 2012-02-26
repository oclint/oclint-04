add_library(OCLintCore
  ClangInstance.cpp
  SmellFinder.cpp
  Violation.cpp
  ViolationSet.cpp
  Version.cpp
  )

add_library(OCLintRuleSet
  RuleConfiguration.cpp
  RuleSet.cpp
)

add_subdirectory(exception)
add_subdirectory(reporter)
add_subdirectory(rule)
add_subdirectory(helper)
add_subdirectory(driver)
