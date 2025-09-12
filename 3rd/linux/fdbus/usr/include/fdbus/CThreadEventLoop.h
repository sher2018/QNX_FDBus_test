/*
 * Copyright (C) 2015   Jeremy Chen jeremy_cz@yahoo.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#ifndef _CTHREADEVENTLOOP_H_
#define _CTHREADEVENTLOOP_H_

#include "CBaseEventLoop.h"
#ifdef CONFIG_STD_CONDVAR
#include <condition_variable>
#else
#include <fdbus/CBaseConditionVariable.h>
#endif

namespace ipc {
namespace fdbus {
class CThreadEventLoop : public CBaseEventLoop
{
public:
    CThreadEventLoop();
    ~CThreadEventLoop();

    void dispatch();
    bool notify();
    bool init(CBaseWorker *worker);
    ELoopType type() const
    {
        return THREAD_LOOP;
    }
private:
    CBaseWorker *mWorker;
#ifdef CONFIG_STD_CONDVAR
    std::condition_variable_any mWakeupSignal;
#else
    CBaseConditionVariable mWakeupSignal;
#endif
};

}
}
#endif
