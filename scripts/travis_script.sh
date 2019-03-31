case "${TRAVIS_OS_NAME}-${CC}" in
  windows-*)
    export CMAKE_BUILD_GENERATOR="Visual Studio 15 2017 Win64"
    ;;

  *-clang)
    export CC=clang
    export CXX=clang++
    export CMAKE_BUILD_GENERATOR=Ninja
    ;;

  *-gcc)
    export CC=gcc-8
    export CXX=g++-8
    export COV=gcov-8
    export CMAKE_BUILD_GENERATOR=Ninja
    ;;
esac

if test "${ENABLE_DOCS}" = "yes"; then
  export CMAKE_OPTS="-Dxxx_docs=yes"
fi

cmake . -G "${CMAKE_BUILD_GENERATOR}" -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ${CMAKE_OPTS}
cmake --build . --config ${BUILD_TYPE}

if test "${BUILD_TYPE}" = "Coverage"; then
  travis_wait cmake --build . --target xxx-cov
else
  ctest --output-on-failure
fi
