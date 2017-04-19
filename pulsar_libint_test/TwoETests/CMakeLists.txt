pulsar_cxx_test(TwoETests TestERI ${STAGE_DIR}${PULSAR_MODULE_DIR}/pulsar_libint)

foreach(x TestERI)
    target_compile_definitions(${x} PRIVATE "-DPULSAR_LIBINT_LIBRARY=\"${PULSAR_LIBINT_LIBRARY}\"")
endforeach()
