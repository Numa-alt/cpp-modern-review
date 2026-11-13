#include "DeviceEventWriter.h"

#include <chrono>
#include <iomanip>

void WriteCurrentTime(std::ostream& ofs)
{
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm localTime{};

#ifdef _WIN32
    localtime_s(&localTime, &t);
#else
    localtime_r(&t, &localTime);
#endif

    ofs << "["
        << std::setfill('0')
        << std::setw(2) << localTime.tm_hour << ":"
        << std::setw(2) << localTime.tm_min << ":"
        << std::setw(2) << localTime.tm_sec
        << "] ";

}

void WriteDeviceEvent(const DeviceEvent& deviceEvent, std::ostream& ofs)
{
    WriteCurrentTime(ofs);

    switch (deviceEvent.mType)
    {
    case DeviceEventType::Update: ofs << "[UPDATE]"; break;
    case DeviceEventType::Warning: ofs << "[WARNING]"; break;
    case DeviceEventType::Error: ofs << "[ERROR]"; break;
    }
    ofs << " device id=" << deviceEvent.mDeviceId;
    ofs << " value=" << deviceEvent.mValue << "\n";
}
