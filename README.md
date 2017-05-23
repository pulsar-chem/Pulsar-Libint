# LibInt/Pulsar Interface

Welcome to the repository for the LibInt/Pulsar interface.  LibInt is a widely
used integrals library for quantum chemistry and this repository ensures it is
callable from the Pulsar framework.

All credit for LibInt goes to the Valeev group at Virginia Tech.  The official
repository is :link:[here](https://github.com/evaleev/libint).  Questions,
comments, and concerns regarding LibInt's operation should be directed there.

This repository simply wraps the LibInt library in a manner consistent with the
Pulsar framework, whose main page is
[here](https://github.com/pulsar-chem/Pulsar-Core).  Questions, comments, and
concerns regarding the integration of LibInt into the Pulsar framework should
be directed to this repository.

## Compiling and Installing

This project will automatically build LibInt
for you (if it can not locate it on your system).  Note that at the moment the
resulting version of LibInt will be somewhat limited relative to a full install
as it will only support up to a relatively low max angular momentum (g-shells,
which limits your basis set to aug-cc-pVQZ for second row atoms), have no
support for geminal integrals, and no derivative support.  To change this tweak
`Pulsar-LibInt/external/CMakeLists.txt` using the build instructions located in
the official LibInt repo.  Alternatively you may download and install your own
LibInt library.  So long as said library's path is included in
`CMAKE_PREFIX_PATH` CMake ought to find it.  Note if you go this route LibInt
must be compiled with `-fPIC` in order to work correctly with Pulsar.

### Requirements
Aside from a somewhat modern version of CMake (3.1+) and C++11 compilers, the
main other requirement is an already installed version of Pulsar.  This module
will download and install LibInt if it is not found.  That said, to use an
already existing LibInt installation, ensure the path to the LibInt's `lib`
directory is included in `CMAKE_PREFIX_PATH` (or alternatively set
`LibInt_LIBRARY` and `LibInt_INCLUDE_DIR` appropriately).  If this module is
building LibInt you will additionally need to satisfy its dependencies, which
are:
- autoconf
- pkg-config
- boost

### Compiling

It should be possible to compile Pulsar-LibInt via some variant of the following

~~~.sh
cmake -H. -Bbuild -DCMAKE_OPTION_1=VALUE_1 -DCMAKE_OPTION_2=...
cd build && make
make install
~~~

Some particularly relevant CMake options are:

- `CMAKE_CXX_COMPILER` This is the C++ compiler to use
- `CMAKE_INSTALL_PREFIX` This is where you want the result to be installed.  If
  not set by the user the module will be installed into Pulsar Core's module
  directory
- `CMAKE_PREFIX_PATH` This is a list of directories where CMake will look for
  dependencies.

### Using the API

TODO: Add link when documentation is automated.


## TODOs

Feel free to work on any of these and submit a PR.

- LibInt supports a host of optimizations.  It should be possible via the CMake
system to automatically determine which of these optimizations should be turned
on.
- In order to be used with Pulsar LibInt needs to have been compiled with
`-fPIC`.  A check for this should be added to `FindLibInt`.
