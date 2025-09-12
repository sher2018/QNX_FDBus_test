/*
 * Copyright (C) 2025 wangcheng 
 * All rights reserved.
 */

#include <iostream>
#include "CTestQnxFdbusClient.h"

namespace test {
namespace client {
CTestQnxFdbusClient::CTestQnxFdbusClient(const char *name, ipc::fdbus::CBaseWorker *worker)
    : ipc::fdbus::CBaseServer(name, worker)
{
    ipc::fdbus::CBaseEndpoint::enableUDP(true);
    ipc::fdbus::CBaseEndpoint::enableAysncRead(true);
    ipc::fdbus::CBaseEndpoint::enableAysncWrite(true);
    ipc::fdbus::CFdbBaseObject::enableTimeStamp(true);
}

CTestQnxFdbusClient::~CTestQnxFdbusClient()
{

}

void CTestQnxFdbusClient::onOnline(const ipc::fdbus::CFdbOnlineInfo &info)
{
    std::cout << "CTestQnxFdbusClient::onOnline: " << info.mSid << info.mQOS << std::endl;
}

void CTestQnxFdbusClient::onOffline(const ipc::fdbus::CFdbOnlineInfo &info)
{
    std::cout << "CTestQnxFdbusClient::onOffline: " << info.mSid << info.mQOS << std::endl;
}

void CTestQnxFdbusClient::onInvoke(ipc::fdbus::CBaseJob::Ptr &msg_ref)
{
    std::cout << "CTestQnxFdbusClient::onInvoke: " << std::endl;
}

void CTestQnxFdbusClient::onBroadcast(ipc::fdbus::CBaseJob::Ptr &msg_ref)
{
    std::cout << "CTestQnxFdbusClient::onBroadcast: " << std::endl;
}

}; /* client */
} /* test */