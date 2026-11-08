#include "Motor.h"

int Motor::GetSpeed() const
{
    return mSpeed;
}
bool Motor::GetMoving() const
{
    return mMoving;
}
void Motor::Update()
{
    std::uint64_t speed = CalcRandom();

    if ((speed % 100) < 50)
    {
        mSpeed = mSpeed + static_cast<int>((speed / 100) % 100);
        if (mSpeed > 1000)
        {
            mSpeed = 1000;
        }
    }
    else
    {
        mSpeed = mSpeed - static_cast<int>((speed / 100) % 100);
        if (mSpeed < 0)
        {
            mSpeed = 0;
        }
    }

    std::uint64_t moving = CalcRandom();
    mMoving = ((moving % 100) < 50);

}
std::string Motor::GetDataString()const
{
    std::string dataString = "Speed = " + std::to_string(mSpeed) + " Moving = " + std::to_string(mMoving);
    return dataString;
}

