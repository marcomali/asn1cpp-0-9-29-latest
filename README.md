asn1cpp: A memory-safe C++ wrapper on top of asn1c
==================================================

This project tries to create a memory-safe and easy to use modern C++ wrapper
around the code generated by the [asn1c project](https://github.com/vlm/asn1c).

The project is completely header-only: just include the headers in your project
and you're ready to use it.

Feel free to explore the `test` folder in order to see examples on how the
library is used.

Requirements
------------

This library only requires that you have a C++11 compliant compiler, and nothing
else.

Building the tests
------------------

The repository includes a series of tests. The tests are not necessary if you
just wish to use the library.

If you wish to build and run them, you need first to install the [Boost
Test](http://www.boost.org/doc/libs/1_64_0/libs/test/doc/html/index.html)
library.

Then you can simply follow the following instructions from the repository's
root folder:

```
git submodule init
git submodule update
mkdir build
cd build
cmake ..
make
```

This will build all the tests. To run the tests, run:

```
ctest -V
```

from the `build` folder you have created.

To run the tests with `valgrind`, run:

```
ctest -D ExperimentalMemCheck -V
```
