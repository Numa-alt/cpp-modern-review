#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue
{
private:
    std::queue<T> mQueue;
    std::mutex mMutex;
    std::condition_variable mConditionvariable;
    bool mStopping = false;

public:
    bool Push(const T& data)
    {
        std::unique_lock<std::mutex> lock(mMutex);
        if (mStopping)
        {
            return false;
        }
        mQueue.push(data);
        lock.unlock();
        mConditionvariable.notify_one();
        return true;
    }

    bool Pop(T& data)
    {
        std::unique_lock<std::mutex> lock(mMutex);

        mConditionvariable.wait(lock, [this]()
            {
                return !mQueue.empty() || mStopping;
            });

        if (mStopping && mQueue.empty())
        {
            return false;
        }

        data = mQueue.front();
        mQueue.pop();
        return true;
    }

    void Stop()
    {
        std::unique_lock<std::mutex> lock(mMutex);
        mStopping = true;
        lock.unlock();
        mConditionvariable.notify_all();
    }
};
