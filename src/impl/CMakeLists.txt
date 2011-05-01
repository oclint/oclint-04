add_executable(mo main.cpp)
target_link_libraries(mo 
  MOCore
  MOException
  MOReporter
  MOUtil
  MORuleSet
  ${MO_COMMON_LINK_LIB}
  dl
  )
  
IF(CMAKE_COMPILER_IS_GNUCXX)
target_link_libraries(mo 
  gcov
  )
ENDIF()

add_subdirectory(mo)
