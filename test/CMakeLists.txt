include_directories(${GTEST_SRC_DIR}/include)

link_directories(${GTEST_BINARY_DIR})

add_executable(mo_test 
  CanaryTest.cpp
  rule/ASTVisitorTest.cpp
  )

target_link_libraries(mo_test
  MORule
  ${MO_COMMON_LINK_LIB}
  gtest
  gtest_main
  dl
  )
  
IF(CMAKE_COMPILER_IS_GNUCXX)
target_link_libraries(mo_test 
  gcov
  )
ENDIF()
