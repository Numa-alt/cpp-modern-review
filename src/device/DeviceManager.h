#pragma once

#include <vector>
#include <memory>

#include "IDevice.h"


class DeviceManager
{
private:
    std::vector<std::unique_ptr<IDevice>> mDevices;
public:
    bool AddDevice(std::unique_ptr<IDevice> device);

    void Update();

    std::size_t GetDeviceCount()const;

    const IDevice* GetDevice(std::size_t index) const;
};