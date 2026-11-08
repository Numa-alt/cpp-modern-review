#include <iostream>
#include <vector>
#include <memory>

#include "item_manager/ItemManager.h"
#include "device/IDevice.h"
#include "device/Motor.h"
#include "device/TemperatureSensor.h"

int main()
{

    std::vector<std::unique_ptr<IDevice>> devices;

    devices.push_back(std::make_unique<Motor>(0, "motorA", 1234, 0, false));
    devices.push_back(std::make_unique<TemperatureSensor>(1, "tempA", 4325, 0));

    for (auto& d : devices)
    {
        std::cout << "id " << d->GetId() << " name " << d->GetName() << "\n";
    }

    for (int i = 0; i < 100; i++)
    {
        for (auto& d : devices)
        {
            d->Update();
            std::cout << "id " << d->GetId() << " name " << d->GetName() << d->GetDataString() << "\n";
        }
    }

    return 0;
}