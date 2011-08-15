SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/rules)

macro(add_mo_rule name)
  set(CMAKE_SHARED_LINKER_FLAGS "-undefined dynamic_lookup")
  
  add_library(${name} SHARED
    ${name}.cpp
    )

  target_link_libraries(${name} 
    ${MO_COMMON_LINK_LIB}
    MOCore
    MOUtil
    MOException
    )

  target_link_libraries(${name} 
    profile_rt
    )

endmacro(add_mo_rule)

add_mo_rule(EmptyIfStatementRule)
add_mo_rule(UnusedFormalParameterRule)
add_mo_rule(CyclomaticComplexityRule)
