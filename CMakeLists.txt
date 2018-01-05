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



    #    # STRINGS / PARSERS
#    add_executable(util_strings examples/strings/strings.cpp)
#    add_executable(util_format examples/strings/format.cpp)
#    add_executable(util_tokenizer examples/strings/tokenizer.cpp)
#    add_executable(util_spirit_parser examples/strings/spirit_parser.cpp)
#    add_executable(util_spirit_grammar examples/strings/spirit_grammar.cpp)
#    add_executable(util_spirit_structure examples/strings/spirit_structure.cpp)
#
#    # CONTAINERS
#    add_executable(util_multi_index examples/containers/multi_index.cpp)
#    add_executable(util_bimap examples/containers/bimap.cpp)
#    add_executable(util_heap examples/containers/heap.cpp)
#    add_executable(util_multiarray examples/containers/multiarray.cpp)
#    add_executable(util_container examples/containers/container.cpp)
#    add_executable(util_graph examples/containers/graph.cpp)
##    add_executable(util_graph_oop examples/containers/graph_oop.cpp)
#    if (${Boost_FOUND})
#        add_executable(util_circularbuffer examples/containers/circularbuffer.cpp)
#        target_link_libraries(util_circularbuffer ${Boost_LIBRARIES})
#    endif()
#
#    # DATA STRUCTURES
#    add_executable(util_optional examples/data_structures/optional.cpp)
#    add_executable(util_any examples/data_structures/any.cpp)
#    add_executable(util_variant examples/data_structures/variant.cpp)
#    add_executable(util_propertytree examples/data_structures/propertytree.cpp)
#    add_executable(util_tribool examples/data_structures/tribool.cpp)
#    add_executable(util_json examples/data_structures/json.cpp)
#
#    # TIME
#    if (${Boost_FOUND})
#        add_executable(util_datetime examples/time/datetime.cpp)
#        target_link_libraries(util_datetime ${Boost_LIBRARIES})
#        add_executable(util_chrono examples/time/chrono.cpp)
#        target_link_libraries(util_chrono ${Boost_LIBRARIES})
#        add_executable(util_timer examples/time/timer.cpp)
#        target_link_libraries(util_timer ${Boost_LIBRARIES})
#    endif()
#
#    # COMMUNICATION
#    add_executable(util_interprocess examples/communication/interprocess.cpp)
#    if (${Boost_FOUND})
#        add_executable(util_asio examples/communication/asio.cpp)
#        target_link_libraries(util_asio ${Boost_LIBRARIES})
#        add_executable(util_simple_web_server examples/communication/simple_web_server.cpp)
#        target_link_libraries(util_simple_web_server ${Boost_LIBRARIES})
#    endif()
#
#    # MEMORY MANAGEMENT
#    add_executable(util_memory_pool examples/memory/memory_pool.cpp) # Manual Management
#    add_executable(util_flyweight_pattern examples/memory/flyweight_pattern.cpp) # Save memory when objects share data
#
#    # ALGORITHMS FOR:
#    add_executable(util_container_algorithms examples/algorithms/algorithms.cpp) # CONTAINER ALGORITHMS
#    add_executable(util_conversion examples/algorithms/conversion.cpp) # RANGE ALGORITHMS
#    if (${Boost_FOUND})
#        add_executable(util_container_range examples/algorithms/range.cpp) # RANGE ALGORITHMS
#        target_link_libraries(util_container_range ${Boost_LIBRARIES})
#    endif()
#
#    # NUMERIC
#    add_executable(util_ublas_algebra examples/numeric/ublas.cpp)
#    add_executable(util_integers examples/numeric/integers.cpp)
#    add_executable(util_accumulators examples/numeric/accumulators.cpp)
#    add_executable(util_numeric_conversion examples/numeric/numeric_conversion.cpp)
#    add_executable(util_geometry examples/numeric/geometry.cpp)
##    add_executable(util_container_overload examples/numeric/container_overload.cpp)
#    add_executable(util_container_shortcuts examples/numeric/container_shortcuts.cpp)
#    add_executable(util_random_shortcuts examples/numeric/random_shortcuts.cpp)
#
#    # PARALLEL
#    add_executable(util_thread_pool examples/parallel/thread_pool.cpp)
#    if (${Boost_FOUND})
#        add_executable(util_parallel_thread examples/parallel/parallel_thread.cpp)
#        target_link_libraries(util_parallel_thread ${Boost_LIBRARIES})
#        add_executable(util_parallel_lockfree examples/parallel/parallel_lockfree.cpp)
#        target_link_libraries(util_parallel_lockfree ${Boost_LIBRARIES})
#        add_executable(util_gpu examples/parallel/gpu.cpp)
#        target_link_libraries(util_gpu ${Boost_LIBRARIES} ${OpenCL_LIBRARIES})
#    endif()
#
#    # PROGRAMMING PARADIGMS
#    add_executable(util_functional_phoenix examples/programming_paradigms/functional_phoenix.cpp)
#    add_executable(util_generic_typetraits examples/programming_paradigms/generic_typetraits.cpp)
#    add_executable(util_generic_fusion_tuples examples/programming_paradigms/generic_fusion_tuples.cpp)
#    add_executable(util_typestring examples/programming_paradigms/typestring.cpp)
#    if (${Boost_FOUND})
#        add_executable(util_coroutine examples/programming_paradigms/coroutine.cpp)
#        target_link_libraries(util_coroutine ${Boost_LIBRARIES})
#    endif()
#
#    # HELPERS
#    add_executable(util_universally_unique_identifiers examples/helpers/universally_unique_identifiers.cpp)
#    add_executable(util_operators examples/helpers/operators.cpp)
#    add_executable(util_stl_shortcuts examples/helpers/stl_shortcuts.cpp)
#    if (${Boost_FOUND})
#        add_executable(util_boost_log examples/helpers/boost_log.cpp)
#        target_link_libraries(util_boost_log ${Boost_LIBRARIES})
#        add_executable(util_program_options examples/helpers/program_options.cpp)
#        target_link_libraries(util_program_options ${Boost_LIBRARIES})
#        add_executable(util_serialization examples/helpers/serialization.cpp)
#        target_link_libraries(util_serialization ${Boost_LIBRARIES})
#    endif()

endif()
