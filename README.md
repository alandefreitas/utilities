# Utilities for Modern C++

This library includes many useful utility functions in the following categories:

* Streaming Data [(examples)](./examples/stream_utils.cpp)
    * Coloured terminal
    * Streaming whole containers
    * Pretty colored and organized tables
    * Coloured logging for debug, info, and error
    * Progress bar on terminal
    * Streaming to containers
    * Streams with regex filters
    * Streams to/from filesystem
    * Plotting results (using gnuplot)
* Data Structures [(examples)](./examples/data_structures_utils.cpp) 
    * JSON
    * Any-data variable
    * Optional data 
    * Property trees
    * Tribooleans with true, false, and indeterminate
    * Variant data
    * Fusion tuples
    * Heterogeneous vectors
* Containers [(examples)](./examples/container_utils.cpp)
    * Graphs
    * Bidirectional maps
    * Multidimensional arrays
    * Recursive vector
    * Stable vector
    * Multi-index container
    * Circular buffer
    * Heap
    * Binomial Heap
* Algorithms [(examples)](./examples/algorithm_utils.cpp)
    * Range-based algorithms (like `sort(a)`, etc)
    * Range views (or filters)
    * Extensions to STL algorithms
    * Hexadecimal conversion
    * Polymorphic Casting
* Numeric Algorithms [(examples)](./examples/numeric_utils.cpp)
    * Helpers for random numbers with all distributions
    * Container generators
    * Numeric methods and statistics
    * Operations between numeric containers
    * Types controlling the size of integers
    * Numeric conversion with overflow detection
    * Basic Linear Algebra Library (UBLAS)
    * Geometry
    * Spacial Indexes 
* Algorithms for Strings [(examples)](./examples/string_utils.cpp)
    * String functions
    * Tokenizing strings
    * Formatted strings
* Helper Functions [(examples)](./examples/container_helpers_utils.cpp)
    * Container numeric overloads (like `vector_c = vector_a + vector_b`, etc)
    * Automatic Relational Operators
    * Serialization
    * Universally Unique Identifiers
    * Program Options
* Parallel Programming [(examples)](./examples/parallel_utils.cpp)
    * Thread Pools
    * GPU / OpenCL
    * Threads example
* Communication [(examples)](./examples/communication_utils.cpp)
    * ASIO steady timer
    * ASIO web client
    * Interprocesses with shared memory
    * HTTP Server
    * HTTP Client
* Programming Paradigms [(examples)](./examples/programming_paradigms_utils.cpp)
    * Demangling
    * Function typetraits
    * Extended Generic Typetraits
    * Coroutines
    * Strings as types
    * Phoenix functional functions
* Time [(examples)](./examples/time_utils.cpp)
    * Timers
    * Clocks, CPU Clocks, Timepoints, and Durations
    * Streaming time
    * Calendar dates and time
    * Location-independent Times
    * Location-dependent Times
    * Formatted Input and Output
* Memory [(examples)](./examples/memory_utils.cpp)
    * Memory Pool
    * Flyweight Pattern (avoiding replicate data in objects)

In can include it in your CMake project with:

```cmake
include(ExternalProject)
ExternalProject_Add(
        utilities
        GIT_REPOSITORY "https://github.com/alandefreitas/utilities.git"
        GIT_TAG "master"
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/utilities"
        PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/include/utilities_prefix"
        # UPDATE_COMMAND ""
)
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include/utilities/find_external_packages.cmake)
    include(${CMAKE_CURRENT_SOURCE_DIR}/include/utilities/find_external_packages.cmake)
endif()
# ... create your target
target_include_directories(my_target PUBLIC ${Utils_INCLUDE_DIRS})
target_link_libraries(my_target ${Utils_LIBRARIES})
```

Then just `#include "utils.cpp"` in your source file.

- [Examples](#examples)
- [Issues](#issues)

## Examples

You can look at all examples in the [`examples`](./examples/) directory.

* Streaming Data [(example)](./examples/stream_utils.cpp)
* Data Structures [(example)](./examples/data_structures_utils.cpp) 
* Containers [(example)](./examples/container_utils.cpp)
* Algorithms [(example)](./examples/algorithm_utils.cpp)
* Numeric Algorithms [(example)](./examples/numeric_utils.cpp)
* Algorithms for Strings [(example)](./examples/string_utils.cpp)
* Helper Functions [(example)](./examples/container_helpers_utils.cpp)
* Parallel Programming [(example)](./examples/parallel_utils.cpp)
* Communication [(example)](./examples/communication_utils.cpp)
* Programming Paradigms [(example)](./examples/programming_paradigms_utils.cpp)
* Time [(example)](./examples/time_utils.cpp)
* Memory [(example)](./examples/memory_utils.cpp)

## Issues
If you have issues, you can:

* [Create a new issue](https://github.com/alandefreitas/utilities/issues/new).
* [Look at closed issues](https://github.com/alandefreitas/utilities/issues?q=is%3Aissue+is%3Aclosed)

Thank you for trying this library. [Send me an email](mailto:alandefreitas@gmail.com) for any special considerations.
