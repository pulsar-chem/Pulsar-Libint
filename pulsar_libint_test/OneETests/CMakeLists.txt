pulsar_cxx_test(OneETests TestNuclearElectron ${STAGE_DIR}${PULSAR_MODULE_DIR}/pulsar_libint)
pulsar_cxx_test(OneETests TestKinetic ${STAGE_DIR}${PULSAR_MODULE_DIR}/pulsar_libint)
pulsar_cxx_test(OneETests TestOverlap ${STAGE_DIR}${PULSAR_MODULE_DIR}/pulsar_libint)

foreach(x TestNuclearElectron TestKinetic TestOverlap)
    target_compile_definitions(${x} PRIVATE "-DPULSAR_LIBINT_LIBRARY=\"${PULSAR_LIBINT_LIBRARY}\"")
endforeach()
