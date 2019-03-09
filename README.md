# XXX short description

[![Build Status](https://travis-ci.org/svens/xxx.svg?branch=master)](https://travis-ci.org/svens/xxx)
[![Coverage](https://coveralls.io/repos/github/svens/xxx/badge.svg?branch=master)](https://coveralls.io/github/svens/xxx?branch=master)

XXX long introduction


## Compiling and installing

    $ mkdir build && cd build
    $ cmake .. [-Dxxx_unittests=yes|no] [-Dxxx_bench=yes|no] [-Dxxx_docs=yes|no]
    $ make && make test && make install


## Source tree

The source tree is organised as follows:

    .               Root of source tree
    |- xxx          Library ...
    |  `- module    ... per module headers/sources/tests
    |- cmake        CMake helper stuff
    |- bench        Benchmarking application
    `- scripts      Helper scripts
