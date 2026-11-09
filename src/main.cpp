#include <iostream>
#include <thread>

#include "device/DeviceManager.h"

#include "device/IDevice.h"
#include "device/Motor.h"
#include "device/TemperatureSensor.h"
#include "device/ThreadSafeQueue.h"
#include "device/DeviceEvent.h"

void DisplayDevicesData(const DeviceManager& deviceManager)
{
    std::size_t deviceCount = deviceManager.GetDeviceCount();

    for (std::size_t i = 0; i < deviceCount; ++i)
    {
        const IDevice* device = deviceManager.GetDevice(i);
        if (device)
        {
            std::cout << "id " << device->GetId() << " " << device->GetName() << " " << device->GetDataString() << "\n";
        }
    }
}

void Producer(DeviceManager& deviceManager, ThreadSafeQueue<DeviceEvent>& queue)
{
    // queue.Push({ DeviceEventType::Update, 1, 10 });
    // queue.Push({ DeviceEventType::Warning, 2, 20 });
    // queue.Push({ DeviceEventType::Error, 3, 4 });

    for (int i = 0; i < 100; i++)
    {
        std::vector<DeviceEvent> deviceEvent = deviceManager.Update();
        for (const auto& e : deviceEvent)
        {
            queue.Push(e);
        }
    }

    queue.Stop();
}
void Consumer(ThreadSafeQueue<DeviceEvent>& queue)
{
    while (true)
    {
        DeviceEvent data{ DeviceEventType::Error,0,0 };
        bool dataExist = queue.Pop(data);
        if (!dataExist)
        {
            break;
        }
        switch (data.mType)
        {
        case DeviceEventType::Update: std::cout << "[UPDATE] "; break;
        case DeviceEventType::Warning: std::cout << "[WARING] "; break;
        case DeviceEventType::Error: std::cout << "[ERROR] "; break;
        }
        std::cout << " id=" << data.mDeviceId << " value=" << data.mValue << "\n";

    }
}


int main()
{
    DeviceManager deviceManager;

    deviceManager.AddDevice(std::make_unique<Motor>(0, "MotorA", 123, 0, false));
    deviceManager.AddDevice(std::make_unique<Motor>(1, "MotorB", 456, 0, false));
    deviceManager.AddDevice(std::make_unique<TemperatureSensor>(2, "TempA", 789, 0));

    // for (int i = 0; i < 100; ++i)
    // {
    //     std::vector<DeviceEvent> deviceEvent = deviceManager.Update();
    //     for (const auto& e : deviceEvent)
    //     {
    //         std::cout << "Id:" << e.mDeviceId << " Event:" << static_cast<int>(e.mType) << " Value:" << e.mValue << "\n";
    //     }
    //     //        DisplayDevicesData(deviceManager);
    // }

    ThreadSafeQueue<DeviceEvent> queue;

    std::thread producer(Producer, std::ref(deviceManager), std::ref(queue));
    std::thread consumer(Consumer, std::ref(queue));

    producer.join();
    consumer.join();


    return 0;
}