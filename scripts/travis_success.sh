if test "${BUILD_TYPE}" = "Coverage"; then
  coveralls-lcov xxx.info
  cmake --build . --target xxx-doc
fi
