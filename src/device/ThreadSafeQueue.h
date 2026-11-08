#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

class ThreadSafeQueue
{
private:
    std::queue<int> mQueue;
    std::mutex mMutex;
    std::condition_variable mConditionvariable;

public:
    void Push(int data)
    {
        std::unique_lock<std::mutex> lock(mMutex);
        mQueue.push(data);
        lock.unlock();
        mConditionvariable.notify_one();
    }
    int Pop()
    {
        std::unique_lock<std::mutex> lock(mMutex);

        mConditionvariable.wait(lock, [this]()
            {
                return !mQueue.empty();
            });
        int data = mQueue.front();
        mQueue.pop();
        return data;
    }

};