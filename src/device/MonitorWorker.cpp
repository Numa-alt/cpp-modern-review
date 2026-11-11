#include "MonitorWorker.h"

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
        mEventCallback(data);
    }
}
