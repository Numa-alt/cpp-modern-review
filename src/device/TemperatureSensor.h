#pragma once

#include "IDevice.h"

class TemperatureSensor : public IDevice
{
private:
    int mTemperature;
public:
    TemperatureSensor(int id, const std::string& name, std::uint64_t randomSeed, int temperature) : IDevice(id, name, randomSeed), mTemperature(temperature)
    {

    }
    int GetTemperature() const;
    void Update() override;
    std::string GetDataString() const override;

};
