#include "TemperatureSensor.h"

int TemperatureSensor::GetTemperature() const
{
    return mTemperature;
}

void TemperatureSensor::Update()
{
    std::uint64_t random = CalcRandom();

    if ((random % 100) < 50)
    {
        mTemperature += static_cast<int>(((random / 100) % 10));
        if (mTemperature > 300)
        {
            mTemperature = 300;
        }
    }
    else
    {
        mTemperature -= static_cast<int>(((random / 100) % 10));
        if (mTemperature < 0)
        {
            mTemperature = 0;
        }
    }
}

std::string TemperatureSensor::GetDataString() const
{
    std::string dataString;
    dataString += "Temperature = " + std::to_string(mTemperature);
    return dataString;
}

DeviceEvent TemperatureSensor::GetEvent() const
{
    DeviceEvent deviceEvent{ DeviceEventType::Update,GetId(),mTemperature };

    if (mTemperature >= 250)
    {
        deviceEvent.mType = DeviceEventType::Error;
    }
    else if (mTemperature >= 200)
    {
        deviceEvent.mType = DeviceEventType::Warning;
    }
    return deviceEvent;
}