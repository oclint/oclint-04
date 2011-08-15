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
  MORuleSetTest
  MOUtilTest
  MOCore
  MOException
  MOReporter
  MORuleSet
  MOUtil
  ${MO_COMMON_LINK_LIB}
  dl
  )
  
target_link_libraries(mo_test 
  profile_rt
  )

add_subdirectory(impl)
