cmake_minimum_required(VERSION 3.1)

project(test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Debug")

aux_source_directory(${PROJECT_SOURCE_DIR}/src SOURCE_DIR)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(test ${SOURCE_DIR})