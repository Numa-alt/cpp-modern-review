#include "Motor.h"

int Motor::GetSpeed() const
{
    return mSpeed;
}

bool Motor::GetWorking() const
{
    return mWorking;
}

void Motor::Update()
{
    std::uint64_t speed = CalcRandom();

    if ((speed % 100) < 50)
    {
        mSpeed = mSpeed + static_cast<int>((speed / 100) % 100);
        if (mSpeed > 1000)
        {
            mSpeed = 1000;
        }
    }
    else
    {
        mSpeed = mSpeed - static_cast<int>((speed / 100) % 100);
        if (mSpeed < 0)
        {
            mSpeed = 0;
        }
    }

    std::uint64_t working = CalcRandom();
    mWorking = ((working % 100) < 50);

}

DeviceEvent Motor::GetEvent() const
{
    DeviceEvent deviceEvent{ DeviceEventType::Update,GetId(),mSpeed };
    if (mSpeed >= 900)
    {
        deviceEvent.mType = DeviceEventType::Error;
    }
    else if (mSpeed >= 800)
    {
        deviceEvent.mType = DeviceEventType::Warning;
    }
    return deviceEvent;
}

std::string Motor::GetDataString() const
{
    std::string dataString = "Speed = " + std::to_string(mSpeed) + " Working = " + std::to_string(mWorking);
    return dataString;
}

