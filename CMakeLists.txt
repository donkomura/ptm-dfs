cmake_minimum_required(VERSION 2.6)
project(ptm-dfs CXX)

set(CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# info sources
set(EXEC_SERVER server)
set(EXEC_CLIENT client)
set(SRC_KV kv.cpp)
set(SRC_RPC rpc.cpp)
set(SRC_SERVER server.cpp)
set(SRC_CLIENT client.cpp)

# package finding
set(CMAKE_PREFIX_PATH /home/obata/pkg/)
find_package(PkgConfig REQUIRED)
find_package(Boost 1.53.0 REQUIRED COMPONENTS program_options)
find_package(quill REQUIRED)

# ptmdb
set(PTMDB_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/durabletx/ptmdb)
set(INCLUDE_PTMDB_DIR ${PTMDB_ROOT})
set(INCLUDE_PTMDB_PORT_DIR ${PTMDB_ROOT}/port)
set(INCLUDE_PTMDB_UTIL_DIR ${PTMDB_ROOT}/util)
set(SRC_PTMS ${PTMDB_ROOT}/db_impl.cc ${PTMDB_ROOT}/status.cc ${PTMDB_ROOT}/port/port_posix.cc ${PTMDB_ROOT}/util/histogram.cc ${PTMDB_ROOT}/util/env_posix.cc ${PTMDB_ROOT}/util/testutil.cc ${PTMDB_ROOT}/write_batch.cc)
## for pmem ops
option(USE_PWB_IS_CLFLUSH "pwd is a CLFLUSH and pfence/psync is nops (default)" OFF)
option(USE_PWB_IS_CLFLUSHOPT "pwd is a CLFLUSHOPT and pfence/psync are SFENCE" OFF)
option(USE_PWB_IS_CLWB "pwd is a CLWB and pfence/psync are SFENCE" OFF)
option(USE_PWB_IS_NOP "pwd/pfence/psync is nops" ON)

if (USE_PWB_IS_CLFLUSH)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPWB_IS_CLFLUSH")
elseif(USE_PWB_IS_CLFLUSHOPT)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPWB_IS_CLFLUSHOPT")
elseif(USE_PWB_IS_CLWB)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPWB_IS_CLWB")
elseif(USE_PWB_IS_NOP)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPWB_IS_NOP")
endif()

## for pmem db log
option(USE_ROMULUS_LOG "use Romulus log" OFF)
option(USE_TRINITY_VR_FC "use TrinityVRFC" OFF)
option(USE_TRINITY_VR_TL2 "use TrinityVRTL2" ON)
option(USE_DUO_VR_FC "use DuoVRFC" OFF)

if (USE_ROMULUS_LOG)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_ROMULUS_LOG")
	MESSAGE(STATUS "not supported Romulus log")
elseif(USE_TRINITY_VR_FC)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_TRINITY_VR_FC")
	SET(SRC_PTMS_DB "${PTMDB_ROOT}/ptmcpp/TrinityVRFC.cpp")
elseif(USE_TRINITY_VR_TL2)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_TRINITY_VR_TL2")
	SET(SRC_PTMS_DB "${PTMDB_ROOT}/ptmcpp/TrinityVRTL2.cpp")
elseif(USE_DUO_VR_FC)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_DUO_VR_FC")
	SET(SRC_PTMS_DB "${PTMDB_ROOT}/ptmcpp/DuoVRFC.cpp")
endif()

pkg_check_modules(thallium thallium REQUIRED)

include_directories(${thallium_INCLUDE_DIRS})
include_directories(${quill_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${INCLUDE_PTMDB_DIR})
include_directories(${INCLUDE_PTMDB_PORT_DIR})
include_directories(${INCLUDE_PTMDB_UTIL_DIR})

add_executable(${EXEC_SERVER} ${SRC_PTMS_DB} ${SRC_SERVER} ${SRC_RPC} ${SRC_KV} ${SRC_PTMS})
# add_executable(${EXEC_SERVER} ${SRC_SERVER} ${SRC_PTMS})
target_link_libraries(${EXEC_SERVER} ${thallium_LIBRARIES})
target_link_libraries(${EXEC_SERVER} ${Boost_LIBRARIES})
target_link_libraries(${EXEC_SERVER} quill::quill)

add_executable(${EXEC_CLIENT} ${SRC_CLIENT})
target_link_libraries(${EXEC_CLIENT} ${thallium_LIBRARIES})
