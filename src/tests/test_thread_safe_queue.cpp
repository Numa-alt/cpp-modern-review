#include "device/ThreadSafeQueue.h"
#include "device/DeviceEvent.h"

#include <cassert>


int main()
{
    ThreadSafeQueue<DeviceEvent> q;

    //PushしたイベントをFIFO順にPopできる
    q.Push(DeviceEvent(DeviceEventType::Update, 0, 0));
    q.Push(DeviceEvent(DeviceEventType::Warning, 1, 1));
    q.Push(DeviceEvent(DeviceEventType::Error, 2, 2));

    DeviceEvent e0{ DeviceEventType::Error,3,3 };
    q.Pop(e0);
    DeviceEvent e1{ DeviceEventType::Error,4,4 };
    q.Pop(e1);
    DeviceEvent e2{ DeviceEventType::Error,5,5 };
    q.Pop(e2);

    assert(e0.mType == DeviceEventType::Update);
    assert(e1.mType == DeviceEventType::Warning);
    assert(e2.mType == DeviceEventType::Error);

    assert(e0.mDeviceId == 0);
    assert(e1.mDeviceId == 1);
    assert(e2.mDeviceId == 2);

    assert(e0.mValue == 0);
    assert(e1.mValue == 1);
    assert(e2.mValue == 2);

#if 0
    //Queueが空になった後popがfalseを返す
    DeviceEvent e3{ DeviceEventType::Error,6,6 };
    bool b = q.Pop(e3);
    assert(b == false);


    //Stop後でもすでにQueueにあるイベントは取り出せる
    q.Push(DeviceEvent(DeviceEventType::Update, 7, 7));
    q.Stop();
    DeviceEvent e6;
    bool bb = q.Pop(e6);
    assert(e6.mType == DeviceEventType::Update);
    assert(e6.mDeviceId == 7);
    assert(e6.mValue == 7);

    bool afterStop = q.Push(DeviceEvent(DeviceEventType::Update, 7, 7));
    assert(afterStop == false);
#endif
    return 0;
}
