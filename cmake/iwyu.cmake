find_program(iwyu NAMES iwyu include-what-you-use)
if(iwyu)
  message(STATUS "Enable iwyu")
  set_property(TARGET ${PROJECT_NAME}
    PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu}
  )
endif()
