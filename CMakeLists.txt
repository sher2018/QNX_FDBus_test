# Copyright (C) 2025 wangcheng 
# All rights reserved.

cmake_minimum_required(VERSION 3.1.3)
set(PROJECT_NAME test_fdbus)

# set QNX compiler
if(NOT DEFINED ENV{QNX_HOST} OR NOT DEFINED ENV{QNX_TARGET})
    message(FATAL_ERROR "QNX_HOST or QNX_TARGET environment variables are not set!")
endif()

set(CMAKE_SYSTEM_NAME QNX)
set(QNX_HOST "$ENV{QNX_HOST}")
set(QNX_TARGET "$ENV{QNX_TARGET}")
message(STATUS "QNX_HOST: ${QNX_HOST}")
message(STATUS "QNX_TARGET: ${QNX_TARGET}")

SET(CMAKE_C_COMPILER ${QNX_HOST}/usr/bin/qcc)
SET(CMAKE_CXX_COMPILER ${QNX_HOST}/usr/bin/q++)

message(STATUS "CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")

# set QNX definations
add_definitions("-D_XOPEN_SOURCE=700")
add_definitions("-D_POSIX_C_SOURCE=199309L")
add_definitions("-D_QNX_SOURCE")

# set cmake options
set(CMAKE_VERBOSE_MAKEFILE ON)

# set project
project(${PROJECT_NAME} C CXX)
message(STATUS "project: ${PROJECT_NAME}")

# set include directories
set(FDBUS_LIB_PATH "${CMAKE_SOURCE_DIR}/3rd/fdbus/usr")
include_directories(
    ${FDBUS_LIB_PATH}/include
    ${FDBUS_LIB_PATH}/include/fdbus
    ${FDBUS_LIB_PATH}/include/fdbus/cJSON
)

set(PROTOBUF_LIB_PATH "${CMAKE_SOURCE_DIR}/3rd/protobuf")
include_directories(
    ${PROTOBUF_LIB_PATH}/include
    ${PROTOBUF_LIB_PATH}/include/google 
    ${PROTOBUF_LIB_PATH}/include/google/protobuf 
    ${PROTOBUF_LIB_PATH}/include/google/protobuf/compiler 
    ${PROTOBUF_LIB_PATH}/include/google/protobuf/compiler/cpp  
    ${PROTOBUF_LIB_PATH}/include/google/protobuf/io 
    ${PROTOBUF_LIB_PATH}/include/google/protobuf/stubs 
    ${PROTOBUF_LIB_PATH}/include/google/protobuf/util 
)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/client
    ${CMAKE_SOURCE_DIR}/src/server
    ${CMAKE_SOURCE_DIR}/src/name_server
)

# set libraries
add_library(${PROJECT_NAME}_client SHARED
    ${CMAKE_SOURCE_DIR}/src/client/CTestQnxFdbusClient.cpp  
)

add_library(${PROJECT_NAME}_server SHARED
    ${CMAKE_SOURCE_DIR}/src/server/CTestQnxFdbusServer.cpp
)

add_library(${PROJECT_NAME}_name_server SHARED
    ${CMAKE_SOURCE_DIR}/src/name_server/CTestQnxFdbusNameServer.cpp
)

# set executable files
add_executable(${PROJECT_NAME}_main
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

# set link libraries 
target_link_directories(${PROJECT_NAME}_main PRIVATE ${CMAKE_SOURCE_DIR}/build)

target_link_directories(${PROJECT_NAME}_main PRIVATE ${FDBUS_LIB_PATH}/lib)
target_link_directories(${PROJECT_NAME}_main PRIVATE ${PROTOBUF_LIB_PATH}/lib)