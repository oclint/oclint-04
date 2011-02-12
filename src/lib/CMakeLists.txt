add_library(MOCore
  SmellFinder.cpp
  )

add_executable(mo main.cpp)
target_link_libraries(mo 
  MOCore
  ${MO_COMMON_LINK_LIB}
  dl
  )
  
IF(CMAKE_COMPILER_IS_GNUCXX)
target_link_libraries(mo 
  gcov
  )
ENDIF()
