foreach(x TestDF)
    pulsar_cxx_test(ThreeCenterTests ${x} ${STAGE_DIR}${PULSAR_MODULE_DIR}/pulsar_libint)
    target_compile_definitions(${x} PRIVATE "-DPULSAR_LIBINT_LIBRARY=\"${PULSAR_LIBINT_LIBRARY}\"")
endforeach()
