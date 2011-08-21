add_executable(mo main.cpp)
target_link_libraries(mo 
  MOCore
  MORuleSet
  MOException
  MOReporter
  MOUtil
  ${MO_COMMON_LINK_LIB}
  dl
  )

if(IS_CI_BUILD)
target_link_libraries(mo 
  profile_rt
  )
endif()

add_subdirectory(mo)
