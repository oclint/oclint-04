add_executable(oclint main.cpp)
target_link_libraries(oclint
  OCLintCore
  OCLintRuleSet
  OCLintException
  OCLintReporter
  OCLintHelper
  OCLintDriver
  ${OCLINT_COMMON_LINK_LIB}
  dl
  )

if(IS_CI_BUILD)
target_link_libraries(oclint
  profile_rt
  )
endif()

add_subdirectory(oclint)
