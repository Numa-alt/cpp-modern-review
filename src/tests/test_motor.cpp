#include "device/Motor.h"
#include "device/DeviceEvent.h"

#include <cassert>

int main()
{
    Motor motor799{ 0,"Motor",12345,799,true };
    DeviceEvent deviceEvent799 = motor799.GetEvent();
    assert(deviceEvent799.mType == DeviceEventType::Update);
    assert(deviceEvent799.mDeviceId == 0);
    assert(deviceEvent799.mValue == 799);

    Motor motor800{ 0,"Motor",12345,800,true };
    DeviceEvent deviceEvent800 = motor800.GetEvent();
    assert(deviceEvent800.mType == DeviceEventType::Warning);
    assert(deviceEvent800.mDeviceId == 0);
    assert(deviceEvent800.mValue == 800);

    Motor motor900{ 0,"Motor",12345,900,true };
    DeviceEvent deviceEvent900 = motor900.GetEvent();
    assert(deviceEvent900.mType == DeviceEventType::Error);
    assert(deviceEvent900.mDeviceId == 0);
    assert(deviceEvent900.mValue == 900);

    return 0;
}