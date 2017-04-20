include(ExternalProject)
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
