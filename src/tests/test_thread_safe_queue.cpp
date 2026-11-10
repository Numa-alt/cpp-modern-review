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

    //Stop後でもすでにQueueにあるイベントは取り出せる
    q.Push(DeviceEvent(DeviceEventType::Update, 6, 6));
    q.Stop();
    DeviceEvent e3{ DeviceEventType::Error,999,999 };
    bool canPop = q.Pop(e3);
    assert(canPop);
    assert(e3.mDeviceId == 6);
    assert(e3.mType == DeviceEventType::Update);
    assert(e3.mValue == 6);

    //Stop済みで、かつQueueが空になったあとPop()がfalse
    DeviceEvent e4{ DeviceEventType::Error,7,7 };
    bool afterStopAndEmptyPop = q.Pop(e4);
    assert(!afterStopAndEmptyPop);

    bool canPush = q.Push(DeviceEvent(DeviceEventType::Update, 8, 8));
    assert(!canPush);

    return 0;
}
