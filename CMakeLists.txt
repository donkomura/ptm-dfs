cmake_minimum_required(VERSION 2.6)

project(ptm-dfs CXX)
set(EXEC_SERVER server)
set(EXEC_CLIENT client)
set(SRC_SERVER rpc.cpp server.cpp)
set(SRC_CLIENT client.cpp)

set(CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

set(CMAKE_PREFIX_PATH /home/obata/pkg/)

find_package(PkgConfig REQUIRED)
find_package(Boost 1.53.0 REQUIRED COMPONENTS program_options)
find_package(quill REQUIRED)

pkg_check_modules(thallium thallium REQUIRED)

include_directories(${thallium_INCLUDE_DIRS})
include_directories(${quill_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

add_executable(${EXEC_SERVER} ${SRC_SERVER})
target_link_libraries(${EXEC_SERVER} ${thallium_LIBRARIES})
target_link_libraries(${EXEC_SERVER} ${Boost_LIBRARIES})
target_link_libraries(${EXEC_SERVER} quill::quill)

add_executable(${EXEC_CLIENT} ${SRC_CLIENT})
target_link_libraries(${EXEC_CLIENT} ${thallium_LIBRARIES})
