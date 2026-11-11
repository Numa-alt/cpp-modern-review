#include <iostream>
#include <thread>

#include "device/DeviceManager.h"

#include "device/IDevice.h"
#include "device/Motor.h"
#include "device/TemperatureSensor.h"
#include "device/ThreadSafeQueue.h"
#include "device/DeviceEvent.h"
#include "device/MonitorWorker.h"


void Producer(DeviceManager& deviceManager, ThreadSafeQueue<DeviceEvent>& queue)
{
    for (int i = 0; i < 100; ++i)
    {
        std::vector<DeviceEvent> deviceEvent = deviceManager.Update();
        for (const auto& e : deviceEvent)
        {
            queue.Push(e);
        }
    }

    queue.Stop();
}

void DisplayDeviceEvent(const DeviceEvent& deviceEvent)
{
    switch (deviceEvent.mType)
    {
    case DeviceEventType::Update: std::cout << "[UPDATE] "; break;
    case DeviceEventType::Warning: std::cout << "[WARNING] "; break;
    case DeviceEventType::Error: std::cout << "[ERROR] "; break;
    }
    std::cout << " id=" << deviceEvent.mDeviceId << " value=" << deviceEvent.mValue << "\n";
}

int main()
{
    DeviceManager deviceManager;

    deviceManager.AddDevice(std::make_unique<Motor>(0, "MotorA", 123, 0, false));
    deviceManager.AddDevice(std::make_unique<Motor>(1, "MotorB", 456, 0, false));
    deviceManager.AddDevice(std::make_unique<TemperatureSensor>(2, "TempA", 789, 0));

    ThreadSafeQueue<DeviceEvent> queue;
    MonitorWorker monitorWorker(queue, DisplayDeviceEvent);

    std::thread producer(Producer, std::ref(deviceManager), std::ref(queue));
    std::thread consumer(&MonitorWorker::Run, &monitorWorker);

    producer.join();
    consumer.join();

    return 0;
}
