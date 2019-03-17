# Template for C++ library project

[![Build Status](https://travis-ci.org/svens/xxx.svg?branch=master)](https://travis-ci.org/svens/xxx)
[![Coverage](https://coveralls.io/repos/github/svens/xxx/badge.svg?branch=master)](https://coveralls.io/github/svens/xxx?branch=master)

Provides tooling for:
* Linux/MacOS/Windows builds using g++, clang++ and MSVC
* CI: [Travis-CI](https://travis-ci.com)
* Unittesting: [Catch2](https://github.com/catchorg/Catch2)
* Code coverage: [gcov](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html)/[lcov](https://github.com/linux-test-project/lcov), [coveralls](https://docs.coveralls.io)
* Documentation: [Doxygen](http://www.doxygen.nl)
* Benchmarking: [Google benchmark](https://github.com/google/benchmark)

To get started, clone this repository, get rid of existing .git directory,
search and replace strings `xxx` and `XXX` with new project name.

Also, in [.travis.yml](https://github.com/svens/xxx/blob/d6f856589eef3e43abf606a59ce9e519aa29d8d2/.travis.yml#L26) replace GITHUB_TOKEN secure variable with new repository-specific value to deploy gh-pages on master builds. For encrypted environment variables, see [Encryption keys](https://docs.travis-ci.com/user/encryption-keys/) guide.


## Compiling and installing

    $ mkdir build && cd build
    $ cmake .. [-Dxxx_unittests=yes|no] [-Dxxx_benchmarks=yes|no] [-Dxxx_docs=yes|no]
    $ make && make test && make install


## Source tree

The source tree is organised as follows:

    .               Root of source tree
    |- xxx          Library ...
    |  `- module    ... per module headers/sources/tests
    |- bench        Benchmarks
    |- cmake        CMake modules
    |- extern       External code as git submodules
    `- scripts      Helper scripts
