#include "device/TemperatureSensor.h"
#include "device/DeviceEvent.h"

#include <cassert>

int main()
{
    TemperatureSensor t250{ 0,"t250",0,250 };
    TemperatureSensor t200{ 1,"t200",0,200 };
    TemperatureSensor t199{ 2,"t199",0,199 };

    DeviceEvent e250 = t250.GetEvent();
    DeviceEvent e200 = t200.GetEvent();
    DeviceEvent e199 = t199.GetEvent();

    assert(e250.mType == DeviceEventType::Error);
    assert(e250.mDeviceId == 0);
    assert(e250.mValue == 250);

    assert(e200.mType == DeviceEventType::Warning);
    assert(e200.mDeviceId == 1);
    assert(e200.mValue == 200);

    assert(e199.mType == DeviceEventType::Update);
    assert(e199.mDeviceId == 2);
    assert(e199.mValue == 199);

    return 0;
}