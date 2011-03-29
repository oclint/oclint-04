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
  MOException
  MOReporter
  # MORule
  MOUtil
  ${MO_COMMON_LINK_LIB}
  dl
  )
  
IF(CMAKE_COMPILER_IS_GNUCXX)
target_link_libraries(mo_test 
  gcov
  )
ENDIF()

add_subdirectory(impl)
