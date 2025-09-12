/*
 * Copyright (C) 2025 wangcheng 
 * All rights reserved.
 */

#ifndef CTESTQNXFDBUSCLIENT_H
#define CTESTQNXFDBUSCLIENT_H

#include "fdbus.h"

namespace test {
namespace client {

class CTestQnxFdbusClient : public ipc::fdbus::CBaseServer 
{
public:
    CTestQnxFdbusClient(const char *name, ipc::fdbus::CBaseWorker *worker = nullptr);
    ~CTestQnxFdbusClient();

protected:
    void onOnline(const ipc::fdbus::CFdbOnlineInfo &info);
    void onOffline(const ipc::fdbus::CFdbOnlineInfo &info);
    void onInvoke(ipc::fdbus::CBaseJob::Ptr &msg_ref);
    void onBroadcast(ipc::fdbus::CBaseJob::Ptr &msg_ref);
};
}; /* client */
} /* test */

#endif /* CTESTQNXFDBUSCLIENT_H */