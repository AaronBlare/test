cmake_minimum_required (VERSION 3.8)

set(PROJECT_NAME oqs)
project(${PROJECT_NAME})

# Set Intel Compiler
set(CMAKE_GENERATOR_TOOLSET "Intel C++ Compiler 19.0" CACHE STRING "Platform Toolset" FORCE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

if (CMAKE_VERSION VERSION_LESS 3.8)
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
else()
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
endif()

include(CTest)
include(cmake/modules/FindMKL.cmake)

include(googletest/DownloadProject.cmake)
download_project(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/google/googletest.git
                 GIT_TAG             master
                 ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

# When using CMake 2.8.11 or later, header path dependencies
# are automatically added to the gtest and gmock targets.
# For earlier CMake versions, we have to explicitly add the
# required directories to the header search path ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include")
endif()

# MKL
find_package(MKL REQUIRED)
if(MKL_FOUND)
	include_directories("${MKL_INCLUDE_DIRS}")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(OQS_LIBRARY "${PROJECT_NAME}_lib")
set(OQS_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/oqs_lib/model")
set(OQS_TEST "${PROJECT_NAME}_test")
set(OQS_MAIN "${PROJECT_NAME}_main")

include_directories("${OQS_INCLUDE}")

enable_testing()

add_subdirectory("oqs_main")
add_subdirectory("oqs_lib/model")
add_subdirectory("oqs_test/model")
