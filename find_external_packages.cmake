# Package Manager
if (NOT EXISTS ${FindPackageOnline})
    file(DOWNLOAD https://raw.githubusercontent.com/alandefreitas/find_package_online/master/FindPackageOnline ${CMAKE_CURRENT_SOURCE_DIR}/FindPackageOnline)
endif()
include(FindPackageOnline)

set(Boost_USE_STATIC_LIBS ON)
set(boost_lib_names chrono filesystem regex system iostreams date_time timer thread coroutine log program_options serialization)
find_package_online(Boost COMPONENTS ${boost_lib_names})
find_package_online(OpenCL)
find_package_online(Gnuplot)
find_package_online(ThreadPool)
find_package_online(JSON)
find_package_online(Gnuplot-iostream)
find_package_online(PrettyPrint)
find_package_online(SimpleServer)
find_package_online(TermColor)
find_package_online(TypeString)

if (UNIX AND NOT APPLE)
    set(LINUX_LIBS ${CMAKE_DL_LIBS} pthread rt)
endif()


set(Utils_INCLUDE_DIRS
    ${Boost_INCLUDE_DIR}
#    SYSTEM
    ${OpenCL_INCLUDE_DIRS}
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
    ${LINUX_LIBS}
    ${Boost_LIBRARIES}
    ${OpenCL_LIBRARIES}
    ${ThreadPool_LIBRARIES}
    ${JSON_LIBRARIES}
    ${Gnuplot-iostream_LIBRARIES}
    ${PrettyPrint_LIBRARIES}
    ${SimpleServer_LIBRARIES}
    ${TermColor_LIBRARIES}
    ${TypeString_LIBRARIES}
    )
