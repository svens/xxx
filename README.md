# Template for C++ library project

[![Build](https://github.com/svens/xxx/workflows/Build/badge.svg)](https://github.com/svens/xxx/actions?query=workflow:Build)
[![Coverage](https://coveralls.io/repos/github/svens/xxx/badge.svg)](https://coveralls.io/github/svens/xxx)

Provides tooling for:
* Linux/MacOS/Windows builds using g++, clang++ and MSVC
* CI: [GitHub Actions](https://github.com/features/actions)
* Unittesting/benchmarking: [Catch2](https://github.com/catchorg/Catch2)
* Code coverage: [gcov](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html)/[lcov](https://github.com/linux-test-project/lcov), [coveralls](https://docs.coveralls.io)
* Documentation: [Doxygen](http://www.doxygen.nl)

To get started, clone this repository, get rid of existing .git directory,
search and replace strings `xxx` and `XXX` with new project name.


## Compiling and installing

    $ mkdir build && cd build
    $ cmake .. [-Dxxx_test=yes|no] [-Dxxx_doc=yes|no] [-Dxxx_samples=yes|no]
    $ make && make test && make install


## Source tree

The source tree is organised as follows:

    .               Root of source tree
    |- xxx          Library ...
    |  `- module    ... per module headers/sources/tests/benchmarks
    |- cmake        CMake modules
    `- sample       Sample application using xxx
