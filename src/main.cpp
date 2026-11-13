#include <iostream>
#include <thread>
#include <stop_token>
#include <chrono>
#include <fstream>
#include <iomanip>

#include "device/DeviceManager.h"

#include "device/IDevice.h"
#include "device/Motor.h"
#include "device/TemperatureSensor.h"
#include "device/ThreadSafeQueue.h"
#include "device/DeviceEvent.h"
#include "device/MonitorWorker.h"


void Producer(std::stop_token stopToken, DeviceManager& deviceManager, ThreadSafeQueue<DeviceEvent>& queue)
{
    while (!stopToken.stop_requested())
    {
        std::vector<DeviceEvent> deviceEvent = deviceManager.Update();
        for (const auto& e : deviceEvent)
        {
            queue.Push(e);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

    }
}

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


int main()
{
    DeviceManager deviceManager;

    deviceManager.AddDevice(std::make_unique<Motor>(0, "MotorA", 123, 0, false));
    deviceManager.AddDevice(std::make_unique<Motor>(1, "MotorB", 456, 0, false));
    deviceManager.AddDevice(std::make_unique<TemperatureSensor>(2, "TempA", 789, 0));

    std::ofstream logFile("device.log", std::ios::app);
    if (!logFile)
    {
        std::cerr << "Failed to open device.log\n";
        return 1;
    }

    ThreadSafeQueue<DeviceEvent> queue;
    MonitorWorker monitorWorker(queue, [&logFile](const DeviceEvent& deviceEvent)
        {
            WriteDeviceEvent(deviceEvent, std::cout);
            WriteDeviceEvent(deviceEvent, logFile);
        });

    std::jthread producer(Producer, std::ref(deviceManager), std::ref(queue));
    std::jthread consumer(&MonitorWorker::Run, &monitorWorker);

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    producer.request_stop();
    producer.join();
    queue.Stop();

    consumer.join();

    return 0;
}
