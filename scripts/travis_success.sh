if test "${BUILD_TYPE}" = "Coverage"; then
  coveralls-lcov xxx.info
fi

if test "${ENABLE_DOCS}" = "yes"; then
  cmake --build . --target xxx-doc
fi
