/*
 * Copyright (C) 2025 wangcheng 
 * All rights reserved.
 */

#include <iostream>
#include "CTestQnxFdbusServer.h"

namespace test {
namespace server {

CTestQnxFdbusServer::CTestQnxFdbusServer(const char *name, ipc::fdbus::CBaseWorker *worker)
    : ipc::fdbus::CBaseServer(name, worker)
{
    ipc::fdbus::CBaseEndpoint::enableUDP(true);
    ipc::fdbus::CBaseEndpoint::enableAysncRead(true);
    ipc::fdbus::CBaseEndpoint::enableAysncWrite(true);
    ipc::fdbus::CFdbBaseObject::enableTimeStamp(true);
}

CTestQnxFdbusServer::~CTestQnxFdbusServer() {
    
}

void CTestQnxFdbusServer::onOnline(const ipc::fdbus::CFdbOnlineInfo &info)
{
    std::cout << "CTestQnxFdbusServer::onOnline: " << info.mSid << info.mQOS << std::endl;
    
    if (info.mFirstOrLast == true) {
        std::cout << "CTestQnxFdbusServer::onOnline: " << " first client connected" << std::endl;
    }
}

void CTestQnxFdbusServer::onOffline(const ipc::fdbus::CFdbOnlineInfo &info)
{
    std::cout << "CTestQnxFdbusServer::onOffline: " << info.mSid << info.mQOS << std::endl;

    if (info.mFirstOrLast == true) {
        std::cout << "CTestQnxFdbusServer::onOffline: " << " last client disconnected" << std::endl;
    }
}

void CTestQnxFdbusServer::onInvoke(ipc::fdbus::CBaseJob::Ptr &msg_ref)
{
    std::cout << "CTestQnxFdbusServer::onInvoke: " << std::endl;
}

void CTestQnxFdbusServer::onSubscribe(ipc::fdbus::CBaseJob::Ptr &msg_ref)
{
    std::cout << "CTestQnxFdbusServer::onSubscribe: " << std::endl;

    auto msg = ipc::fdbus::castToMessage<ipc::fdbus::CBaseMessage *>(msg_ref);
    switch (msg->code()) {
        case CTEST_QNX_FDBUS_CLIENT_MSG:
            std::cout << "CTestQnxFdbusServer::onSubscribe: client msg" << std::endl;
            break;
        default:
            std::cout << "CTestQnxFdbusServer::onSubscribe: code:" << msg->code() << std::endl;
    }
}

}; /* server */
} /* test */