# Copyright (C) 2025 wangcheng 
# All rights reserved.

cmake_minimum_required(VERSION 3.1.3)
set(PROJECT_NAME test_fdbus)

# set options
option(ENABLE_QNX_COMPILER "Enable QNX compiler" OFF)
option(ENABLE_PROTOBUF_LIB "Enable protobuf library" OFF)

# set QNX compiler
if(ENABLE_QNX_COMPILER) 
    if(NOT DEFINED ENV{QNX_HOST} OR NOT DEFINED ENV{QNX_TARGET})
        message(FATAL_ERROR "QNX_HOST or QNX_TARGET environment variables are not set! source qnxsdp-env.sh first!")
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
endif() # ENABLE_QNX_COMPILER

# set cmake options
set(CMAKE_VERBOSE_MAKEFILE ON)

# set project
project(${PROJECT_NAME} C CXX)
message(STATUS "project: ${PROJECT_NAME}")

# set include directories
if(ENABLE_QNX_COMPILER) 
    set(FDBUS_LIB_PATH "${CMAKE_SOURCE_DIR}/3rd/qnx/fdbus/usr")
    set(PROTOBUF_LIB_PATH "${CMAKE_SOURCE_DIR}/3rd/qnx/protobuf")
else()
    set(FDBUS_LIB_PATH "${CMAKE_SOURCE_DIR}/3rd/linux/fdbus/usr")
    set(PROTOBUF_LIB_PATH "${CMAKE_SOURCE_DIR}/3rd/linux/protobuf")
endif() # ENABLE_QNX_COMPILER

include_directories(
    ${FDBUS_LIB_PATH}/include
    ${FDBUS_LIB_PATH}/include/fdbus
    ${FDBUS_LIB_PATH}/include/fdbus/cJSON
)

if (ENABLE_PROTOBUF_LIB)
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
endif() # ENABLE_PROTOBUF_LIB

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/client
    ${CMAKE_SOURCE_DIR}/src/server
    ${CMAKE_SOURCE_DIR}/src/name_server
    ${CMAKE_SOURCE_DIR}/src/host_server
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

add_library(${PROJECT_NAME}_host_server SHARED
    ${CMAKE_SOURCE_DIR}/src/host_server/CTestQnxFdbusHostServer.cpp
)

# set executable files
if(CTEST_QNX_FDBUS_SERVER) 
    set(EXECUTABLE_FILE "${PROJECT_NAME}_main_server")
elseif(CTEST_QNX_FDBUS_CLIENT)
    set(EXECUTABLE_FILE "${PROJECT_NAME}_main_client")
else()
    set(EXECUTABLE_FILE "${PROJECT_NAME}_main")
endif()

add_executable(${EXECUTABLE_FILE}
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

# set link libraries 
target_link_directories(${EXECUTABLE_FILE} PRIVATE ${CMAKE_SOURCE_DIR}/build)

target_link_directories(${EXECUTABLE_FILE} PRIVATE ${FDBUS_LIB_PATH}/lib)

if (ENABLE_PROTOBUF_LIB)
    target_link_directories(${EXECUTABLE_FILE} PRIVATE ${PROTOBUF_LIB_PATH}/lib)
endif() # ENABLE_PROTOBUF_LIB