#include "device/MonitorWorker.h"
#include "device/DeviceEvent.h"
#include "device/ThreadSafeQueue.h"

#include <cassert>
#include <vector>

int main()
{
    ThreadSafeQueue<DeviceEvent> queue;
    queue.Push(DeviceEvent(DeviceEventType::Update, 0, 0));
    queue.Push(DeviceEvent(DeviceEventType::Update, 1, 1));
    queue.Push(DeviceEvent(DeviceEventType::Update, 2, 2));
    queue.Stop();
    std::vector<DeviceEvent> eventlog;

    MonitorWorker monitorWorker(queue, [&eventlog](const DeviceEvent& deviceEvent)
        {
            eventlog.push_back(deviceEvent);
        });

    monitorWorker.Run();

    assert(eventlog.size() == 3);

    DeviceEvent ev0 = eventlog[0];
    assert(ev0.mType == DeviceEventType::Update);
    assert(ev0.mDeviceId == 0);
    assert(ev0.mValue == 0);

    DeviceEvent ev1 = eventlog[1];
    assert(ev1.mType == DeviceEventType::Update);
    assert(ev1.mDeviceId == 1);
    assert(ev1.mValue == 1);

    DeviceEvent ev2 = eventlog[2];
    assert(ev2.mType == DeviceEventType::Update);
    assert(ev2.mDeviceId == 2);
    assert(ev2.mValue == 2);

    return 0;
}