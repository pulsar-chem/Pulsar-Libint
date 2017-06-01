foreach(x TestDF)
    pulsar_cxx_test(ThreeCenterTests ${x} ${PULSAR_LIBINT_PREFIX})
    target_compile_definitions(${x} PRIVATE "-DPULSAR_LIBINT_LIBRARY=\"${PULSAR_LIBINT_PREFIX}/pulsar_libint.so\"")
endforeach()
