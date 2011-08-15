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
  
target_link_libraries(mo 
  profile_rt
  )

add_subdirectory(mo)
