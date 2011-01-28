include_directories(${MO_SOURCE_DIR}/third-party/cxxtest)
include_directories(${MO_SOURCE_DIR})

add_executable(mo_test 
  mo_test.cpp
  )

target_link_libraries(mo_test
  MORule
  ${MO_COMMON_LINK_LIB}
  dl
  )
  
IF(CMAKE_COMPILER_IS_GNUCXX)
target_link_libraries(mo_test 
  gcov
  )
ENDIF()
