#pragma once

#include "DeviceEvent.h"
#include "IDevice.h"

class Motor : public IDevice
{
private:
    int mSpeed;
    bool mWorking;
public:
    Motor(int id, const std::string& name, std::uint64_t randomSeed, int speed, bool working) : IDevice(id, name, randomSeed), mSpeed(speed), mWorking(working)
    {

    }

    int GetSpeed() const;
    bool GetWorking() const;
    void Update() override;
    std::string GetDataString() const override;

    DeviceEvent GetEvent() const override;

};