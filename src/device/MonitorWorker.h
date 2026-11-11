#pragma once

#include <functional>

#include "DeviceEvent.h"
#include "ThreadSafeQueue.h"

using EventCallback = std::function<void(const DeviceEvent& deviceEvent)>;

class MonitorWorker
{
private:
    ThreadSafeQueue<DeviceEvent>& mQueue;
    EventCallback mEventCallback;
public:
    MonitorWorker(ThreadSafeQueue<DeviceEvent>& queue, EventCallback callback) :mQueue(queue), mEventCallback(callback)
    {
    }
    void Run();
};
