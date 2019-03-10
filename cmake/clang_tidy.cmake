find_program(clang_tidy NAMES clang-tidy)
if(clang_tidy)
  message(STATUS "Enable clang-tidy")
  set_property(TARGET ${PROJECT_NAME}
    PROPERTY CXX_CLANG_TIDY ${clang_tidy}
  )
endif()
