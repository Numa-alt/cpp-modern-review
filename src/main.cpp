#include <iostream>

#include "device/DeviceManager.h"

#include "device/IDevice.h"
#include "device/Motor.h"
#include "device/TemperatureSensor.h"

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

int main()
{
    DeviceManager deviceManager;

    deviceManager.AddDevice(std::make_unique<Motor>(0, "MotorA", 123, 0, false));
    bool f = deviceManager.AddDevice(std::make_unique<Motor>(1, "MotorB", 456, 0, false));

    if (f)
    {
        std::cout << "success!\n";
    }
    else {
        std::cout << "failed\n";
    }
    deviceManager.AddDevice(std::make_unique<TemperatureSensor>(2, "TempA", 789, 0));

    for (int i = 0; i < 100; ++i)
    {
        deviceManager.Update();
        DisplayDevicesData(deviceManager);
    }


    return 0;
}