# (C) 2020 The University of Chicago 
# See COPYRIGHT in top-level directory.
cmake_minimum_required (VERSION 3.17)
project (soma C CXX)
set (CMAKE_CXX_STANDARD 17)
enable_testing ()

add_definitions (-g -Wextra -Wall -Wpedantic)

option (ENABLE_TESTS    "Build tests" OFF)
option (ENABLE_EXAMPLES "Build examples" OFF)
option (ENABLE_BEDROCK  "Build bedrock module" ON)

# add our cmake module directory to the path
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
     "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# link shared lib with full rpath
set (CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set (CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# setup cache variables for ccmake
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Release
         CACHE STRING "Choose the type of build." FORCE)
    set_property (CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
                  "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif ()
set (CMAKE_PREFIX_PATH "" CACHE STRING "External dependencies path")
set (BUILD_SHARED_LIBS "ON" CACHE BOOL "Build a shared library")

find_package (PkgConfig REQUIRED)
# search fo thallium
find_package (thallium REQUIRED)
# search for uuid
pkg_check_modules (UUID REQUIRED IMPORTED_TARGET uuid)
# comment if you don't need abt-io
pkg_check_modules (ABTIO REQUIRED IMPORTED_TARGET abt-io)
# search for nlohmann/json
find_package (nlohmann_json REQUIRED)
# search for TCLAP
find_package (TCLAP REQUIRED)
# search for spdlog
find_package(spdlog REQUIRED)
# search for conduit
find_package(Conduit REQUIRED)
# search of bedrock if needed
if (${ENABLE_BEDROCK})
    find_package(bedrock REQUIRED)
endif ()

#
# Provide default CONDUIT_DIR that works in a conduit install
#
#if(NOT CONDUIT_DIR)
#    set(CONDUIT_DIR "../")
#endif()

#
# Check for valid conduit install
#

# if given relative path, resolve
#get_filename_component(CONDUIT_DIR ${CONDUIT_DIR} ABSOLUTE)
# check for expected cmake exported target files
#if(NOT EXISTS ${CONDUIT_DIR}/lib/cmake/conduit/ConduitConfig.cmake)
#    message(FATAL_ERROR "Could not find Conduit CMake include file (${CONDUIT_DIR}/lib/cmake/conduit/ConduitConfig.cmake)")
#endif()

#
# Use CMake's find_package to import conduit's targets
# using explicit path
#
#find_package(Conduit REQUIRED
#             NO_DEFAULT_PATH 
#             PATHS ${CONDUIT_DIR}/lib/cmake/conduit)


# library version set here (e.g. for shared libs).
set (SOMA_VERSION_MAJOR 0)
set (SOMA_VERSION_MINOR 1)
set (SOMA_VERSION_PATCH 0)
set (SOMA_VERSION
     "${SOMA_VERSION_MAJOR}.${SOMA_VERSION_MINOR}.${SOMA_VERSION_PATCH}")

add_subdirectory (src)
if(${ENABLE_TESTS})
  pkg_check_modules (cppunit REQUIRED IMPORTED_TARGET cppunit)
  add_subdirectory (tests)
endif(${ENABLE_TESTS})
if(${ENABLE_EXAMPLES})
  add_subdirectory (examples)
endif(${ENABLE_EXAMPLES})
