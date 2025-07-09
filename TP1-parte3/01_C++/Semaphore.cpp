#include "Semaphore.h"

Semaphore::Semaphore(int initial) : value(initial) {}

void Semaphore::wait()
{
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this]()
            { return value > 0; });
    --value;
}

void Semaphore::release()
{
    std::unique_lock<std::mutex> lock(mtx);
    ++value;
    cv.notify_one();
}