#pragma once

enum class DeviceEventType
{
    Update,
    Warning,
    Error,
};

struct DeviceEvent
{
    DeviceEventType mType;
    int mDeviceId;
    int mValue;

    DeviceEvent(DeviceEventType type, int deviceId, int value) : mType(type), mDeviceId(deviceId), mValue(value)
    {

    }
};
