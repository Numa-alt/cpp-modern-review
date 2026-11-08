#pragma once

#include "IDevice.h"

class Motor : public IDevice
{
private:
    int mSpeed;
    bool mMoving;
public:
    Motor(int id, const std::string& name, std::uint64_t randomSeed, int speed, bool moving) : IDevice(id, name, randomSeed), mSpeed(speed), mMoving(moving)
    {

    }
    int GetSpeed() const;
    bool GetMoving() const;
    void Update() override;
    std::string GetDataString() const override;

};