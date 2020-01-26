case "${TRAVIS_OS_NAME}-${CC}" in
  linux-clang)
    export CC=clang-9
    export CXX=clang++-9
    export CMAKE_BUILD_GENERATOR=Ninja
    ;;

  linux-gcc)
    export CC=gcc-8
    export CXX=g++-8
    export COV=gcov-8
    export CMAKE_BUILD_GENERATOR=Ninja
    ;;

  osx-clang)
    export CC=clang
    export CXX=clang++
    export CMAKE_BUILD_GENERATOR=Ninja
    ;;

  osx-gcc)
    export CC=gcc-9
    export CXX=g++-9
    export COV=gcov-9
    export CMAKE_BUILD_GENERATOR=Ninja
    ;;

  windows-*)
    export CMAKE_BUILD_GENERATOR="Visual Studio 15 2017 Win64"
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
