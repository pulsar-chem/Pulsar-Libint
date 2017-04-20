# LibInt2/Pulsar Interface

Welcome to the repository for the LibInt2/Pulsar interface.  LibInt2 is a widely
used integrals library for quantum chemistry and this repository ensures it is
callable from the Pulsar framework.

All credit for LibInt2 goes to the Valeev group at Virginia Tech.  The official
repository is [here](https://github.com/evaleev/libint).  Questions, comments,
and concerns regarding LibInt2's operation should be directed there.

This repository simply wraps the LibInt2 library in a manner consistent with the
Pulsar framework, whose main page is
[here](https://github.com/pulsar-chem/Pulsar-Core).  Questions, comments, and
concerns regarding the integration of LibInt2 into the Pulsar framework should
be directed to this repository.

## General Considerations

At the moment I am primarily interested in ensuring I have wrapped LibInt2
correctly so I am compiling with low angular momentum, no geminal integrals,
and no derivatives.  To change this tweak `Pulsar-LibInt/CMakeLists.txt`.  In
there is a thin wrapper around LibInt2's build system and it should be
self-explanatory as to how to use any of LibInt2's build options from that file.

## Compiling and Installing

### Requirements
Aside from a somewhat modern version of CMake (3.1+) and C++11 compilers, the
main other requirement is an already installed version of Pulsar.  This module
will download and install LibInt2 if it is not found.  That said, to use an
already existing LibInt2 installation, ensure the path to the LibInt2's `lib`
directory is included in `CMAKE_PREFIX_PATH` (or alternatively set
`LIBINT2_LIBRARY` and `LIBINT2_INCLUDE_DIR` appropriately).  If this module is
building LibInt2 you will additionally need to satisfy its dependencies, which
are:
- autoconf
- pkg-config
- boost

## TODOs

Feel free to work on any of these and submit a PR.

- LibInt2 supports a host of optimizations.  It should be possible via the CMake
system to automatically determine which of these optimizations should be turned
on.
- In order to be used with Pulsar LibInt2 needs to have been compiled with
`-fPIC`.  A check for this should be added to `FindLibInt2`.
