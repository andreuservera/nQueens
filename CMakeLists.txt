cmake_minimum_required(VERSION 3.1)

project(queens)

set(CMAKE_GENERATOR "Unix Makefiles")
message("generator is set to ${CMAKE_GENERATOR}")

set (CMAKE_CXX_STANDARD 20)

set (EXTERNAL_LIBS "/usr/lib/x86_64-linux-gnu")
#list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
#find_package(MySQL REQUIRED)

include_directories(/usr/include)

add_subdirectory(src)
