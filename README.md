Pulsar-Libint
=============

Libint is a widely used integrals library for computing integrals involving
electrons in quantum chemistry.  Pulsar-Libint provides Pulsar bindings for
Libint allowing it to be called from the Pulsar framework (main page is
:link:[here](https://github.com/pulsar-chem/Pulsar-Core)).

All credit for Libint goes to the Valeev group at Virginia Tech.  The official
repository is :link:[here](https://github.com/evaleev/libint).  Questions,
comments, and concerns regarding Libint's operation should be directed there.

Contents
========
- [Obtaining Pulsar-Libint and Dependencies](#obtaining-pulsar-libint-and-dependencies)
- [Building Pulsar-Libint](#building-pulsar-libint)

Obtaining Pulsar-Libint and Dependencies
----------------------------------------

The official repository for the Pulsar-Libint interface is located
:link:[here](https://github.com/pulsar-chem/Pulsar-Libint).  The source code for
the interface can be obtined via the normal git clone command, *i.e.*
```.sh
git clone https://github.com/pulsar-chem/Pulsar-Libint.git
```

The only dependency of Pulsar-Libint (aside from the Pulsar framework) is
Libint.  There are two options for how Pulsar-Libint can be provided a version
of Libint:

1. The path to an already installed Libint is provided to Pulsar-Libint during
the configure step, or
2. You let Pulsar-Libint compile Libint for you

Although the latter choice is convenient it is worth mentioning some caveats.
First, Libint depends on Boost.  If your version of Boost is not installed in a
standard location, you will need to provide the path to it.  Second, the
resulting version of LibInt will be somewhat limited relative to a full install.
Namely, it will: only support a relatively low max angular momentum (g-shells,
which limits your basis set to aug-cc-pVQZ for second row atoms), have no
support for geminal integrals, and have no derivative support.  These options
are choosen to minimize the build time while still providing the functionality
needed by other Pulsar supermodules.

Building Pulsar-Libint
-------------------------

As with most Pulsar supermodules, Pulsar-Libint uses CMake for the configuration
step.  The result is that configuration should be possible via some variant of:
```.sh
cmake -Bbuild -H. -DOPTION1=VALUE1 -DOPTION2=...
```

Some influential CMake variables you may want to consider setting are:
| Option Name            | Default                 | Description |
|:----------------------:|:-----------------------:|-------------|
| CMAKE_C_COMPILER       | N/A | This is the C compiler to use.  By default CMake will try to find a C compiler on your system. Typically this means it will find  `/bin/gcc`.  |
| CMAKE_CXX_COMPILER     | N/A | Similar to above, except for the C++ compiler. |
| CMAKE_C_FLAGS          | N/A | Any additional flags you want to pass to the C compiler. |
| CMAKE_CXX_FLAGS | N/A | Any additional flags you want to pass to the C++ compiler. |
| CMAKE_BUILD_TYPE | Release | Can be used to enable debug builds.  Valid choices are: `Release`, `Debug`, or `RelWithDebInfo`. |
| CMAKE_PREFIX_PATH | N/A | Used to tell CMake additional places to look for dependencies.  CMake will look for executables in `CMAKE_PREFIX_PATH/bin/`, libraries in `CMAKE_PREFIX_PATH/lib/`, *etc*. |
| CMAKE_INSTALL_PREFIX | `/usr` | The root directory where the final project will be installed following usual GNU conventions.  *i.e.* libraries will be installed to `CMAKE_INSTALL_PREFIX/lib`, header files to `CMAKE_INSTALL_PREFIX/include`, *etc.* |

After a successful configuration, it should be possible to complete the
installation simply by issuing the commands:
```.sh
cd build && make
make install
```

## Using the API

TODO: Add link when documentation is automated.


## TODOs

Feel free to work on any of these and submit a PR.

- LibInt supports a host of optimizations.  It should be possible via the CMake
system to automatically determine which of these optimizations should be turned
on.
- In order to be used with Pulsar LibInt needs to have been compiled with
`-fPIC`.  A check for this should be added to `FindLibInt`.
