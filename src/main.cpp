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

void Producer(ThreadSafeQueue<DeviceEvent>& queue)
{
    std::cout << "Producer start\n";
    std::cout << "Producer push 1\n";
    queue.Push({ DeviceEventType::Update, 1, 10 });
    std::cout << "Producer push 2\n";
    queue.Push({ DeviceEventType::Warning, 2, 20 });
    std::cout << "Producer push 3\n";
    queue.Push({ DeviceEventType::Error, 3, 4 });
    std::cout << "Producer stop\n";
    queue.Stop();
    std::cout << "Producer end\n";
}
void Consumer(ThreadSafeQueue<DeviceEvent>& queue)
{
    std::cout << "Consumer start\n";
    while (true)
    {
        DeviceEvent data{ DeviceEventType::Error,0,0 };
        bool dataExist = queue.Pop(data);
        if (!dataExist)
        {
            break;
        }
        std::cout << "type " << static_cast<int>(data.mType) << " id " << data.mDeviceId << " value " << data.mValue << "\n";

    }
    std::cout << "Consumer end\n";
}


int main()
{
    ThreadSafeQueue<DeviceEvent> queue;

    std::thread producer(Producer, std::ref(queue));
    std::thread consumer(Consumer, std::ref(queue));

    producer.join();
    consumer.join();

    // DeviceManager deviceManager;

    // deviceManager.AddDevice(std::make_unique<Motor>(0, "MotorA", 123, 0, false));
    // bool f = deviceManager.AddDevice(std::make_unique<Motor>(1, "MotorB", 456, 0, false));

    // if (f)
    // {
    //     std::cout << "success!\n";
    // }
    // else {
    //     std::cout << "failed\n";
    // }
    // deviceManager.AddDevice(std::make_unique<TemperatureSensor>(2, "TempA", 789, 0));

    // for (int i = 0; i < 100; ++i)
    // {
    //     deviceManager.Update();
    //     DisplayDevicesData(deviceManager);
    // }


    return 0;
}