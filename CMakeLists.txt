cmake_minimum_required(VERSION 3.3)
project(SyscallExtension)

set(CMAKE_LINKER_OPTIONS "")

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_LINKER_OPTIONS "${CMAKE_LINKER_OPTIONS} -undefined dynamic_lookup -Qunused-arguments")
elseif("${CMAKE_CXX_COMPILER_ID}" STEQUAL "GNU")
    set(CMAKE_LINKER_OPTIONS "${CMAKE_LINKER_OPTIONS} -Wl,-unresolved-symbols=ignore-in-shared-libs")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_LINKER_OPTIONS} -std=c++11 -DDART_SHARED_LIB -fPIC")

set(SOURCE_FILES src/syscall_extension.cpp src/os.h src/os_posix.cpp src/common.cpp src/common.h src/xpc_connection.cpp src/xpc_connection.h)
include_directories(include)
add_library(syscall_extension SHARED ${SOURCE_FILES})
file(COPY src/syscall.dart DESTINATION .)
