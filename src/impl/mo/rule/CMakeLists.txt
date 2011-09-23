macro(build_dynamic_rule name)
  set(CMAKE_SHARED_LINKER_FLAGS "-undefined dynamic_lookup")
  
  add_library(${name} SHARED
    ${name}.cpp
    )
  
  SET_TARGET_PROPERTIES(${name}
    PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/rules
    )

  target_link_libraries(${name} 
    ${MO_COMMON_LINK_LIB}
    MOCore
    MOUtil
    MOException
    )
endmacro(build_dynamic_rule)

macro(build_dynamic_rules rules)
  FOREACH(it ${rules})
    build_dynamic_rule(${it})
  ENDFOREACH(it)
endmacro(build_dynamic_rules)

macro(build_static_rules rules)
  SET(cpp_files)
  FOREACH(it ${rules})
    list(APPEND cpp_files ${it}.cpp)
  ENDFOREACH(it)
  
  add_library(MORule ${cpp_files})
endmacro(build_static_rules)

SET(LIST_OF_RULES 
  EmptyIfStatementRule
  UnusedLocalVariableRule
  CyclomaticComplexityRule
  )

build_static_rules("${LIST_OF_RULES}")
build_dynamic_rules("${LIST_OF_RULES}")
