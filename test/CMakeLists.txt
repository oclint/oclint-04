include_directories(${OCLINT_SOURCE_DIR}/third-party/cxxtest)
include_directories(${OCLINT_SOURCE_DIR})
include_directories(${OCLINT_SOURCE_DIR}/test/headers)

add_executable(oclint_test
  oclint_test.cpp
  )

target_link_libraries(oclint_test
  CanaryTest
  OCLintCoreTest
  OCLintExceptionTest
  OCLintReporterTest
  OCLintRuleTest
  OCLintUtilTest
  OCLintCore
  OCLintRuleSet
  OCLintRule
  OCLintException
  OCLintReporter
  OCLintUtil
  ${OCLINT_COMMON_LINK_LIB}
  dl
  )

if(IS_CI_BUILD)
target_link_libraries(oclint_test 
  profile_rt
  )
endif()

add_subdirectory(impl)
