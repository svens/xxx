# Template for C++ library project

[![Build Status](https://travis-ci.org/svens/xxx.svg?branch=master)](https://travis-ci.org/svens/xxx)
[![Coverage](https://coveralls.io/repos/github/svens/xxx/badge.svg?branch=master)](https://coveralls.io/github/svens/xxx?branch=master)

Provides tooling for:
* Linux/MacOS/Windows builds using g++, clang++ and MSVC
* Documentation: [Doxygen](http://www.doxygen.nl)
* Unittests: [Catch2](https://github.com/catchorg/Catch2)
* Test coverage: [gcov](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html)/[lcov](https://github.com/linux-test-project/lcov), [coveralls](https://docs.coveralls.io)
  For local viewing pleasure, CMAKE_BUILD_TYPE=Coverage will generate report in ${CMAKE_BINARY_DIR}/cov/ directory
* Micro-benchmarks: [Google benchmark](https://github.com/google/benchmark)

To get started, clone this repository, get rid of existing .git directory,
search and replace strings `xxx` and `XXX` with new project name.


## Compiling and installing

    $ mkdir build && cd build
    $ cmake .. [-Dxxx_unittests=yes|no] [-Dxxx_bench=yes|no] [-Dxxx_docs=yes|no]
    $ make && make test && make install


## Source tree

The source tree is organised as follows:

    .               Root of source tree
    |- xxx          Library ...
    |  `- module    ... per module headers/sources/tests
    |- bench        Benchmarks
    |- cmake        CMake modules
    |- scripts      Helper scripts
    `- tps          External code as git submodules
