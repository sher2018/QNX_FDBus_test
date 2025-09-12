/*
 * Copyright (C) 2025 wangcheng 
 * All rights reserved.
 */

#ifndef CTESTQNXFDBUSSERVER_H
#define CTESTQNXFDBUSSERVER_H

#include "fdbus.h"

namespace test {
namespace server {

typedef enum {
    CTEST_QNX_FDBUS_CLIENT_MSG = 1,
    CTEST_QNX_FDBUS_MSG_MAX_CODE
} CTestQnxFdbusMsgCode;

class CTestQnxFdbusServer : public ipc::fdbus::CBaseServer
{
public:
    CTestQnxFdbusServer(const char *name, ipc::fdbus::CBaseWorker *worker = nullptr);
    ~CTestQnxFdbusServer();

protected:
    void onOnline(const ipc::fdbus::CFdbOnlineInfo &info);
    void onOffline(const ipc::fdbus::CFdbOnlineInfo &info);
    void onInvoke(ipc::fdbus::CBaseJob::Ptr &msg_ref);
    void onSubscribe(ipc::fdbus::CBaseJob::Ptr &msg_ref);
};
}; /* server */
} /* test */

#endif /* CTESTQNXFDBUSSERVER_H */