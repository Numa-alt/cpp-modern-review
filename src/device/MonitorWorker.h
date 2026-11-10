#pragma once

#include "DeviceEvent.h"
#include "ThreadSafeQueue.h"

class MonitorWorker
{
private:
    ThreadSafeQueue<DeviceEvent>& mQueue;
public:
    MonitorWorker(ThreadSafeQueue<DeviceEvent>& queue) :mQueue(queue)
    {
    }
    void Run();
};
