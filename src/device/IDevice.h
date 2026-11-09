#pragma once

#include <string>
#include <cstdint>

#include "DeviceEvent.h"

class IDevice
{
private:
    int mId;
    std::string mName;
    std::uint64_t mRandom;
public:
    IDevice(int id, const std::string& name, std::uint64_t randomSeed) : mId(id), mName(name)
    {
        if (randomSeed == 0)
        {
            mRandom = 12345;
        }
        else {
            mRandom = randomSeed;
        }
    }
    virtual ~IDevice() {}
    int GetId() const { return mId; };
    const std::string& GetName() const { return mName; };
    virtual void Update() = 0;
    std::uint64_t CalcRandom()
    {
        mRandom ^= (mRandom << 13);
        mRandom ^= (mRandom >> 17);
        mRandom ^= (mRandom << 11);
        return mRandom;
    }
    virtual std::string GetDataString() const = 0;

    virtual DeviceEvent GetEvent() const = 0;
};
