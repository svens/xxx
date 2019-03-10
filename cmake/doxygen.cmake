find_package(Doxygen)

if(DOXYGEN_FOUND)
  message(STATUS "Enable documentation")
  configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/Doxyfile.in
    ${CMAKE_BINARY_DIR}/Doxyfile
  )
  add_custom_target(${PROJECT_NAME}-doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating documentation"
  )
else()
  message(STATUS "Disable documentation")
endif()
