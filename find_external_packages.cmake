# Package Manager
#if (NOT EXISTS ${FindPackageOnline})
#    file(DOWNLOAD https://raw.githubusercontent.com/alandefreitas/find_package_online/master/FindPackageOnline ${CMAKE_CURRENT_SOURCE_DIR}/FindPackageOnline)
#endif()
include(FindPackageOnline)

set(Boost_USE_STATIC_LIBS ON)
set(boost_lib_names filesystem regex system iostreams date_time chrono timer thread coroutine log program_options serialization)
find_package_online(Boost REQUIRED COMPONENTS ${boost_lib_names})

find_package_online(OpenCL REQUIRED)

find_package_online(Gnuplot REQUIRED)

find_package_online(Plot REQUIRED)

find_package_online(ThreadPool REQUIRED)

find_package_online(JSON REQUIRED)

find_package_online(Gnuplot-iostream REQUIRED)

find_package_online(PrettyPrint REQUIRED)

find_package_online(SimpleServer REQUIRED)

find_package_online(TermColor REQUIRED)

find_package_online(TypeString REQUIRED)

find_package_online(Range REQUIRED)

set(Utils_INCLUDE_DIRS
    ${Boost_INCLUDE_DIR}
    SYSTEM ${OpenCL_INCLUDE_DIRS}
    ${Plot_INCLUDE_DIRS}
    ${ThreadPool_INCLUDE_DIRS}
    ${JSON_INCLUDE_DIRS}
    ${Gnuplot-iostream_INCLUDE_DIRS}
    ${PrettyPrint_INCLUDE_DIRS}
    ${SimpleServer_INCLUDE_DIRS}
    ${TermColor_INCLUDE_DIRS}
    ${TypeString_INCLUDE_DIRS}
    ${CMAKE_CURRENT_LIST_DIR}/include
    )

set(Utils_LIBRARIES
    ${Boost_LIBRARIES}
    SYSTEM ${OpenCL_LIBRARIES}
    ${Plot_LIBRARIES}
    ${ThreadPool_LIBRARIES}
    ${JSON_LIBRARIES}
    ${Gnuplot-iostream_LIBRARIES}
    ${PrettyPrint_LIBRARIES}
    ${SimpleServer_LIBRARIES}
    ${TermColor_LIBRARIES}
    ${TypeString_LIBRARIES})