cmake_minimum_required(VERSION 2.6)

project(ptm-dfs CXX)
set(EXEC_MAIN main)
set(SRC_MAIN main.cpp)

set(CMAKE_CXX_FLAGS "-std=c++14 -Wall")
set(CMAKE_PREFIX_PATH /home/obata/pkg/)

find_package(PkgConfig REQUIRED)
find_package(Boost 1.53.0 REQUIRED COMPONENTS program_options)
find_package(quill REQUIRED)

pkg_check_modules(thallium thallium REQUIRED)

include_directories(${thallium_INCLUDE_DIRS})
include_directories(${quill_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

message(STATUS "thallium include: ${thallium_INCLUDE_DIRS}")
message(STATUS "boost include: ${Boost_INCLUDE_DIRS}")
message(STATUS "boost lib: ${Boost_LIBRARIES}")
message(STATUS "thallium lib: ${thallium_LIBRARIES}")

add_executable(${EXEC_MAIN} ${SRC_MAIN})
target_link_libraries(${EXEC_MAIN} ${thallium_LIBRARIES})
target_link_libraries(${EXEC_MAIN} ${Boost_LIBRARIES})
target_link_libraries(${EXEC_MAIN} quill::quill)
