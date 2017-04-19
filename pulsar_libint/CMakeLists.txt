cmake_minimum_required(VERSION 3.1)
project(pulsar-Libint CXX)
find_package(pulsar REQUIRED)
find_package(LibInt2 REQUIRED)
include(ExternalProject)

get_filename_component(LIBINT_ROOT ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

add_library(pulsar_libint MODULE creator.cpp
                                 pulsar_libint.cpp
)
target_compile_options(pulsar_libint PRIVATE ${PULSAR_CXX_STRICT_FLAGS})

target_include_directories(pulsar_libint PRIVATE pulsar ${LIBINT_ROOT}
                                         ${LIBINT2_INCLUDE_DIRS}
)
target_link_libraries(pulsar_libint PRIVATE pulsar
                                            ${LIBINT2_LIBRARIES}
)
install(TARGETS pulsar_libint
        LIBRARY DESTINATION ${PULSAR_MODULE_DIR}/pulsar_libint
)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        DESTINATION ${PULSAR_MODULE_DIR}
        FILES_MATCHING PATTERN "*.py"
)
