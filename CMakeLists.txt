cmake_minimum_required(VERSION 2.8)
project(sampler CXX)

# Find and use Boost.
find_package(Boost REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

# default build type: Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

# default install prefix: ~/.local
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local"
      CACHE PATH "Install path prefix, prepended onto install directories."
      FORCE)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")

# Set default architecture flags to optimize for the current system,
# but don't override user settings.
if(NOT CMAKE_CXX_FLAGS MATCHES "-march|-mtune")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og")
endif()

install(FILES ${PROJECT_NAME}.conf DESTINATION ${PROJECT_NAME})
install(DIRECTORY tables DESTINATION ${PROJECT_NAME})
install(DIRECTORY DESTINATION ${PROJECT_NAME}/results)

add_subdirectory(src)
