# Functions and Pre-build  -----------------------------------

# Stop messy in source builds
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt." )
endif()

# Start Build Config -----------------------------------
cmake_minimum_required(VERSION 3.6)
set(CMAKE_SKIP_RPATH true)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE ON)

# Start the project
project(hdbpp-es-metrics LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

configure_file(cmake/FetchEventSubscriber.cmake.in hdbpp_es-download/CMakeLists.txt)

execute_process(
    COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/hdbpp_es-download" )

execute_process(
    COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/hdbpp_es-download" )

add_subdirectory("${CMAKE_BINARY_DIR}/hdbpp_es-src")

# add hdbpp-es project
configure_file(cmake/FetchLibHdbpp.cmake.in libhdbpp-download/CMakeLists.txt)

execute_process(
    COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/libhdbpp-download" )

execute_process(
    COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/libhdbpp-download" )

# add libhdbpp project
add_subdirectory("${CMAKE_BINARY_DIR}/libhdbpp-src" EXCLUDE_FROM_ALL)

# include the metrics library
add_subdirectory(metrics-library EXCLUDE_FROM_ALL)

# For ease of use, we set the output to our projects build directory,
# making linking and running easy. Also we force C++14, since the metrics
# library is coded against recent C++ standards
set_target_properties(hdbpp_es
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)

set_property(
    TARGET hdbpp_es
    APPEND PROPERTY
        LINK_LIBRARIES libhdbpp_shared_library metrics_library)

# Output libhdbpp to the build directly so we can quickly run the hdb++es
set_target_properties(libhdbpp_shared_library
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")