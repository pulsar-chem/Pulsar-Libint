cmake_minimum_required(VERSION 3.2)
project(pulsar-libint-test CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS False)
# CMake doesn't support Intel CXX standard until cmake 3.6
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Intel")
  if("${CMAKE_VERSION}" VERSION_LESS "3.6")
      add_compile_options(-std=c++${CMAKE_CXX_STANDARD})
  endif()
endif()

find_package(pulsar CONFIG REQUIRED)

foreach(dir TwoCenterTests ThreeCenterTests FourCenterTests)
  add_subdirectory(${dir})
  install(FILES ${CMAKE_BINARY_DIR}/${dir}/CTestTestfile.cmake DESTINATION ${dir})
endforeach()

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        DESTINATION .
        FILES_MATCHING PATTERN "*.hpp"
)
# This file was created from the various add_test commands
install(FILES ${CMAKE_BINARY_DIR}/CTestTestfile.cmake DESTINATION .)
