#include "DeviceManager.h"

#include <cassert>
#include <algorithm>


bool DeviceManager::AddDevice(std::unique_ptr<IDevice> device)
{
    const auto it = std::find_if(mDevices.begin(), mDevices.end(), [&device](const std::unique_ptr<IDevice>& d)
        {
            return device->GetId() == d->GetId();
        });

    if (it != mDevices.end())
    {
        return false;
    }
    mDevices.push_back(std::move(device));
    return true;
}

std::vector<DeviceEvent> DeviceManager::Update()
{
    std::vector<DeviceEvent> deviceEventList;

    for (auto& d : mDevices)
    {
        d->Update();
        deviceEventList.push_back(d->GetEvent());
    }

    return deviceEventList;
}

std::size_t DeviceManager::GetDeviceCount() const
{
    return mDevices.size();
}

const IDevice* DeviceManager::GetDevice(std::size_t index) const
{
    assert(index < mDevices.size());
    return mDevices[index].get();
}