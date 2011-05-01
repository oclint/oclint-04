SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/rules)

macro(add_mo_rule name)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -undefined dynamic_lookup")
  
  add_library(${name} SHARED
    ${name}.cpp
    )

  target_link_libraries(${name} 
    ${MO_COMMON_LINK_LIB}
    MOCore
    MOUtil
    MOException
    )

  IF(CMAKE_COMPILER_IS_GNUCXX)
  target_link_libraries(${name} 
    gcov
    )
  ENDIF()
endmacro(add_mo_rule)

add_mo_rule(EmptyIfStatementRule)
