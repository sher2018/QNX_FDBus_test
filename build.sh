# Copyright (C) 2025 wangcheng 
# All rights reserved.

#!/bin/bash

set -e
# set -x 

BUILD_ROOT_DIR=$(pwd)
BUILD_DIR=${BUILD_ROOT_DIR}/build
BUILD_LINUX_DIR=${BUILD_DIR}/linux
BUILD_LINUX_TEST_DIR=${BUILD_LINUX_DIR}/test
BUILD_LINUX_TEST_SRV_DIR=${BUILD_LINUX_TEST_DIR}/srv
BUILD_LINUX_TEST_CLT_DIR=${BUILD_LINUX_TEST_DIR}/clt
BUILD_QNX_DIR=${BUILD_DIR}/qnx
BUILD_QNX_TEST_DIR=${BUILD_QNX_DIR}/test
BUILD_QNX_TEST_SRV_DIR=${BUILD_QNX_TEST_DIR}/srv
BUILD_QNX_TEST_CLT_DIR=${BUILD_QNX_TEST_DIR}/clt

[ -d ${BUILD_DIR} ] && rm -rf ${BUILD_DIR}
mkdir -p ${BUILD_LINUX_TEST_SRV_DIR}
mkdir -p ${BUILD_LINUX_TEST_CLT_DIR}
mkdir -p ${BUILD_QNX_TEST_SRV_DIR}
mkdir -p ${BUILD_QNX_TEST_CLT_DIR}

# build linux
cd ${BUILD_LINUX_DIR}
cmake ${BUILD_ROOT_DIR} || { echo "Linux CMake failed"; exit 1; }
make || { echo "Linux Make failed"; exit 1; }

cd ${BUILD_LINUX_TEST_SRV_DIR}
cmake -DCTEST_QNX_FDBUS_SERVER=1 ${BUILD_ROOT_DIR} || { echo "Linux CMake srv failed"; exit 1; }
make || { echo "Linux Make srv failed"; exit 1; }

cd ${BUILD_LINUX_TEST_CLT_DIR}
cmake -DCTEST_QNX_FDBUS_CLIENT=1 ${BUILD_ROOT_DIR} || { echo "Linux CMake clt failed"; exit 1; }
make || { echo "Linux Make clt failed"; exit 1; }

# # build qnx
cd ${BUILD_QNX_DIR}
cmake -DENABLE_QNX_COMPILER=ON ${BUILD_ROOT_DIR} || { echo "QNX CMake failed"; exit 1; }
make || { echo "QNX Make failed"; exit 1; }

cd ${BUILD_QNX_TEST_SRV_DIR}
cmake -DENABLE_QNX_COMPILER=ON -DCTEST_QNX_FDBUS_SERVER=1 ${BUILD_ROOT_DIR} || { echo "QNX CMake srv failed"; exit 1; }
make || { echo "QNX Make srv failed"; exit 1; }

cd ${BUILD_QNX_TEST_CLT_DIR}
cmake -DENABLE_QNX_COMPILER=ON -DCTEST_QNX_FDBUS_CLIENT=1 ${BUILD_ROOT_DIR} || { echo "QNX CMake clt failed"; exit 1; }
make || { echo "QNX Make clt failed"; exit 1; }

cd ${BUILD_ROOT_DIR}
echo "\e[33m$(date '+%Y-%m-%d %H:%M:%S') build \e[42;30msuccess\e[0m"