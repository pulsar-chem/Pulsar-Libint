cmake_minimum_required(VERSION 3.1)
project(pulsar-Libint-superbuild CXX)

include(ExternalProject)

############################
# Build type
############################
# Default to Release if build type not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

##################################################
# Where stuff will be installed. This is passed
# to other external projects
##################################################
# Note that CMAKE_INSTALL_PREFIX is always absolute
# (cmake makes it that way). Therefore it always begins
# with a slash
set(STAGE_DIR            "${CMAKE_BINARY_DIR}/stage")
set(STAGE_INSTALL_PREFIX "${STAGE_DIR}${CMAKE_INSTALL_PREFIX}")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Where targets should search for dependencies
# Ie, the original CMAKE_PREFIX_PATH, plus the installation stage
list(APPEND CMAKE_PREFIX_PATH ${STAGE_INSTALL_PREFIX})
find_package(LibInt2)

if(NOT LIBINT2_FOUND)
    set(LIBINT_PREFIX ${CMAKE_BINARY_DIR}/libint)
    set(LIBINT_FLAGS ${CMAKE_CXX_FLAGS} -fPIC)
    ExternalProject_Add(libint
        PREFIX ${LIBINT_PREFIX}
        GIT_REPOSITORY https://github.com/evaleev/libint
        GIT_TAG 33560a073efa5a0abd88a37486e552c954808f1d
        PATCH_COMMAND ./autogen.sh
        CONFIGURE_COMMAND ${LIBINT_PREFIX}/src/libint/configure
                            CXX=${CMAKE_CXX_COMPILER}
                            CXXFLAGS=${LIBINT_FLAGS}
                            --prefix=${CMAKE_INSTALL_PREFIX}
                            --enable-eri=0
                            --enable-eri3=0
                            --enable-eri2=0
                            --with-max-am=4
                            --disable-t1g12-support
        BUILD_COMMAND make
        INSTALL_COMMAND make install DESTDIR=${STAGE_DIR}
    )
else()
    add_library(libint INTERFACE)
endif()

ExternalProject_Add(pulsar_libint
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/pulsar_libint
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
               -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    BUILD_ALWAYS 1
    INSTALL_COMMAND ${CMAKE_MAKE_PROGRAM} install DESTDIR=${STAGE_DIR}
    CMAKE_CACHE_ARGS -DCMAKE_PREFIX_PATH:LIST=${CMAKE_PREFIX_PATH}
                     -DCMAKE_INSTALL_RPATH:LIST=${CMAKE_INSTALL_RPATH}
                     -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
                     -DCMAKE_MODULE_PATH:LIST=${CMAKE_MODULE_PATH}
)
add_dependencies(pulsar_libint libint)
###############################
# Pulsar LibInt tests
###############################


ExternalProject_Add(pulsar_libint_test
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/pulsar_libint_test
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/test_stage
               -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
               -DSTAGE_DIR=${STAGE_DIR}
    BUILD_ALWAYS 1
    CMAKE_CACHE_ARGS -DCMAKE_PREFIX_PATH:LIST=${CMAKE_PREFIX_PATH}
                     -DCMAKE_INSTALL_RPATH:LIST=${CMAKE_INSTALL_RPATH}
                     -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
)
add_dependencies(pulsar_libint_test pulsar_libint)


# This file will allow us to run ctest in the top-level build dir
# Basically it just defers to the actual top-level CTestTestfile.cmake in the
# build directory for this project
file(WRITE ${CMAKE_BINARY_DIR}/CTestTestfile.cmake "subdirs(test_stage)")

# Install the staging directory
install(DIRECTORY ${CMAKE_BINARY_DIR}/stage/${CMAKE_INSTALL_PREFIX}/
        DESTINATION ${CMAKE_INSTALL_PREFIX} USE_SOURCE_PERMISSIONS)

