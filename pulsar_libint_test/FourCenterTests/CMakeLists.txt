foreach(x TestERI)
    pulsar_cxx_test(FourCenterTests ${x} ${PULSAR_LIBINT_PREFIX})
    target_compile_definitions(${x} PRIVATE "-DPULSAR_LIBINT_LIBRARY=\"${PULSAR_LIBINT_PREFIX}/pulsar_libint.so\"")
endforeach()
