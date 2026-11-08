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
    }
    int Pop()
    {
        std::unique_lock<std::mutex> lock(mMutex);
        int data = mQueue.front();
        mQueue.pop();
        lock.unlock();
        return data;
    }

};