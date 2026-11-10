#include "MonitorWorker.h"

#include <iostream>

void MonitorWorker::Run()
{
    while (true)
    {
        DeviceEvent data{ DeviceEventType::Error,0,0 };
        bool dataExist = mQueue.Pop(data);
        if (!dataExist)
        {
            break;
        }

        switch (data.mType)
        {
        case DeviceEventType::Update: std::cout << "[UPDATE] "; break;
        case DeviceEventType::Warning: std::cout << "[WARNING] "; break;
        case DeviceEventType::Error: std::cout << "[ERROR] "; break;
        }

        std::cout << " id=" << data.mDeviceId << " value=" << data.mValue << "\n";

    }
}
