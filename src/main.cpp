/*
 * Copyright (C) 2025 wangcheng 
 * All rights reserved.
 */

#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "fdbus.h"

#include "CTestQnxFdbusServer.h"
#include "CTestQnxFdbusServerMain.hpp"
#include "CTestQnxFdbusClient.h"
#include "CTestQnxFdbusClientMain.hpp"
#include "CTestQnxFdbusNameServer.h"
#include "CTestQnxFdbusHostServer.h"

int main(int /*argc*/, char* /*argv*/[])
{
#ifdef CTEST_QNX_FDBUS_SERVER
    return testQnxFdbusServerMain();
#elif defined CTEST_QNX_FDBUS_CLIENT
    return testQnxFdbusClientMain();
#endif
}