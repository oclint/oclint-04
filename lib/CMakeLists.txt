add_definitions(
  -fno-rtti
  -fPIC
  )

IF(CMAKE_COMPILER_IS_GNUCXX)
add_definitions(
  -fprofile-arcs 
  -ftest-coverage
  )
ENDIF()

add_executable(mo main.cpp)
target_link_libraries(mo 
  MORule
  ${MO_COMMON_LINK_LIB}
  dl
  )
  
IF(CMAKE_COMPILER_IS_GNUCXX)
target_link_libraries(mo 
  gcov
  )
ENDIF()

add_subdirectory(rule)
