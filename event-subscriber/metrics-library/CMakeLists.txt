cmake_minimum_required(VERSION 3.6)
project(metric-tests)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Prepare an interface library for the metrics headers
set(METRICS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_library(metrics_library INTERFACE)
target_include_directories(metrics_library INTERFACE ${METRICS_INCLUDE_DIR})
target_link_libraries(metrics_library INTERFACE Threads::Threads)
