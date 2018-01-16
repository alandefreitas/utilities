#######################################################
### SETTINGS                                        ###
#######################################################
cmake_minimum_required(VERSION 3.8)
project(utilities)

set(CMAKE_CXX_STANDARD 14)

#######################################################
### EXTERNAL                                        ###
#######################################################
include(find_external_packages.cmake)

#######################################################
### EXECUTABLE BINARIES                             ###
#######################################################

if((NOT DEFINED UTILS_INCLUDE_TESTS) OR (${UTILS_INCLUDE_TESTS}))

    add_executable(stream_utils examples/stream_utils.cpp)
    target_include_directories(stream_utils PUBLIC ${Utils_INCLUDE_DIRS})
    target_link_libraries(stream_utils ${Utils_LIBRARIES})
    target_compile_options(stream_utils PUBLIC -DPROJECTFOLDER="${CMAKE_CURRENT_SOURCE_DIR}")

    add_executable(data_structures_utils examples/data_structures_utils.cpp)
    target_include_directories(data_structures_utils PUBLIC ${Utils_INCLUDE_DIRS})
    target_link_libraries(data_structures_utils ${Utils_LIBRARIES})

    add_executable(string_utils examples/string_utils.cpp)
    target_include_directories(string_utils PUBLIC ${Utils_INCLUDE_DIRS})
    target_link_libraries(string_utils ${Utils_LIBRARIES})

    add_executable(algorithm_utils examples/algorithm_utils.cpp)
    target_include_directories(algorithm_utils PUBLIC ${Utils_INCLUDE_DIRS})
    target_link_libraries(algorithm_utils ${Utils_LIBRARIES})

    add_executable(container_utils examples/container_utils.cpp)
    target_include_directories(container_utils PUBLIC ${Utils_INCLUDE_DIRS})
    target_link_libraries(container_utils ${Utils_LIBRARIES})

    add_executable(container_helpers_utils examples/container_helpers_utils.cpp)
    target_include_directories(container_helpers_utils PUBLIC ${Utils_INCLUDE_DIRS})
    target_link_libraries(container_helpers_utils ${Utils_LIBRARIES})

    add_executable(numeric_utils examples/numeric_utils.cpp)
    target_include_directories(numeric_utils PUBLIC ${Utils_INCLUDE_DIRS})
    target_link_libraries(numeric_utils ${Utils_LIBRARIES})

    add_executable(time_utils examples/time_utils.cpp)
    target_include_directories(time_utils PUBLIC ${Utils_INCLUDE_DIRS})
    target_link_libraries(time_utils ${Utils_LIBRARIES})

    add_executable(parallel_utils examples/parallel_utils.cpp)
    target_include_directories(parallel_utils PUBLIC ${Utils_INCLUDE_DIRS})
    target_link_libraries(parallel_utils ${Utils_LIBRARIES})

    add_executable(communication_utils examples/communication_utils.cpp)
    target_include_directories(communication_utils PUBLIC ${Utils_INCLUDE_DIRS})
    target_link_libraries(communication_utils ${Utils_LIBRARIES})

    add_executable(memory_utils examples/memory_utils.cpp)
    target_include_directories(memory_utils PUBLIC ${Utils_INCLUDE_DIRS})
    target_link_libraries(memory_utils ${Utils_LIBRARIES})

    add_executable(programming_paradigms_utils examples/programming_paradigms_utils.cpp)
    target_include_directories(programming_paradigms_utils PUBLIC ${Utils_INCLUDE_DIRS})
    target_link_libraries(programming_paradigms_utils ${Utils_LIBRARIES})

    add_executable(parser_utils examples/parser_utils.cpp)
    target_include_directories(parser_utils PUBLIC ${Utils_INCLUDE_DIRS})
    target_link_libraries(parser_utils ${Utils_LIBRARIES})

endif()
