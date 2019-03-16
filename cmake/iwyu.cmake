find_program(iwyu_exe NAMES iwyu include-what-you-use)

function(iwyu target_name)
  if(iwyu_exe)
    set_property(TARGET ${target_name}
      PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_exe}
    )
  endif()
endfunction()
