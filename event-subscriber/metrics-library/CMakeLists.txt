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

# Make test executable
set(METRIC_TEST_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_executable(metric-tests ${METRIC_TEST_SOURCES})
target_compile_options(metric-tests PRIVATE -Wall -Wextra -g)

target_link_libraries(metric-tests 
    PRIVATE metrics_library)

target_include_directories(metric-tests 
    PRIVATE ${PROJECT_SOURCE_DIR})

set_target_properties(metric-tests 
    PROPERTIES 
        LINK_FLAGS "-Wl,--no-undefined"
        CXX_STANDARD 14)

if(DO_CLANG_TIDY)
    set_target_properties(metric-tests  
        PROPERTIES 
            CXX_CLANG_TIDY ${DO_CLANG_TIDY})
endif(DO_CLANG_TIDY)