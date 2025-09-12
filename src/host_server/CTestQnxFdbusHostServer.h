/*
 * Copyright (C) 2025 wangcheng 
 * All rights reserved.
 */

#ifndef CTESTQNXFDBUSHOSTSERVER_H
#define CTESTQNXFDBUSHOSTSERVER_H

#include "fdbus.h"

namespace test {
namespace server {

class CTestQnxFdbusHostServer : public ipc::fdbus::CBaseServer 
{
public:
    CTestQnxFdbusHostServer();
    ~CTestQnxFdbusHostServer();

};
}; /* server */
} /* test */

#endif /* CTESTQNXFDBUSHOSTSERVER_H */