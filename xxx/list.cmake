add_library(${PROJECT_NAME}
  xxx/__bits/platform_sdk.hpp
  xxx/error.hpp
  xxx/error.cpp
)

find_program(clang_tidy NAMES clang-tidy)
if(clang_tidy)
  message(STATUS "Enable clang-tidy")
  set_property(TARGET ${PROJECT_NAME}
    PROPERTY CXX_CLANG_TIDY ${clang_tidy}
  )
endif()

find_program(iwyu NAMES iwyu include-what-you-use)
if(iwyu)
  message(STATUS "Enable iwyu")
  set_property(TARGET ${PROJECT_NAME}
    PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu}
  )
endif()
