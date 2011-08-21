include_directories(${MO_SOURCE_DIR}/third-party/cxxtest)
include_directories(${MO_SOURCE_DIR})
include_directories(${MO_SOURCE_DIR}/test/headers)

add_executable(mo_test 
  mo_test.cpp
  )

target_link_libraries(mo_test  
  CanaryTest
  MOCoreTest
  MOExceptionTest
  MOReporterTest
  MORuleTest
  MOUtilTest
  MOCore
  MORuleSet
  MOException
  MOReporter
  MOUtil
  ${MO_COMMON_LINK_LIB}
  dl
  )

if(IS_CI_BUILD)
target_link_libraries(mo_test 
  profile_rt
  )
endif()

add_subdirectory(impl)
