find_program(clang_tidy_exe NAMES clang-tidy)

function(tidy target_name)
  if(clang_tidy_exe)
    set_property(TARGET ${target_name}
      PROPERTY CXX_CLANG_TIDY ${clang_tidy_exe}
    )
  endif()
endfunction()
