add_executable(mo main.cpp)
target_link_libraries(mo 
  MOCore
  MOException
  MORule
  MOUtil
  MOCore # TODO: will remove this line when we dynamically load these rules
  ${MO_COMMON_LINK_LIB}
  dl
  )
  
IF(CMAKE_COMPILER_IS_GNUCXX)
target_link_libraries(mo 
  gcov
  )
ENDIF()

add_subdirectory(mo)
