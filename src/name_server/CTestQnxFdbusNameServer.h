/*
 * Copyright (C) 2025 wangcheng 
 * All rights reserved.
 */

#ifndef CTESTQNXFDBUSNAMESERVER_H
#define CTESTQNXFDBUSNAMESERVER_H

#include "fdbus.h"

namespace test {
namespace server {

class CTestQnxFdbusNameServer : public ipc::fdbus::CBaseServer
{
public:
    CTestQnxFdbusNameServer();
    ~CTestQnxFdbusNameServer();

};
}; /* server */
} /* test */

#endif /* CTESTQNXFDBUSNAMESERVER_H */