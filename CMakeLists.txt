cmake_minimum_required(VERSION 3.8)  # Ensure you have at least CMake 3.8
project(iTAP VERSION 1.0 LANGUAGES C CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)
if(NOT DEFINED CMAKE_CUDA_ARCHITECTURES)
  set(CMAKE_CUDA_ARCHITECTURES 86)
endif()
# compile and link CUDA code separately from the rest of your code to
# speed up the build process and reduce the size of your final executable.
set(CMAKE_CUDA_SEPARABLE_COMPILATION ON)
set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -Wall -O3 --extended-lambda")

# set compilation flags
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to Release ")
  set(
    CMAKE_BUILD_TYPE Release
    CACHE
    STRING "Choose the type of build."
    FORCE
  )
  # Set the possible values of build type for cmake-gui
  set_property(
    CACHE
    CMAKE_BUILD_TYPE
    PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo"
  )
endif()

set(CMAKE_VERBOSE_MAKEFILE ON)

set(ITAP_3RD_PARTY_DIR ${PROJECT_SOURCE_DIR}/3rd-party)
set(ITAP_EXAMPLE_DIR ${PROJECT_SOURCE_DIR}/examples)

# -----------------------------------------------------------------------------
# must-have package include
# -----------------------------------------------------------------------------
include(CheckLanguage)

# Enable test
include(CTest)
set(CMAKE_CTEST_ARGUMENTS "--output-on-failure")

add_subdirectory(itap)
add_subdirectory(examples)
add_subdirectory(unittests)























































