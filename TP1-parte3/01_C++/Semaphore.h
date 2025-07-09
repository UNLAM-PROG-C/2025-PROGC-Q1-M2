#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex>
#include <condition_variable>

class Semaphore
{
private:
    std::mutex mtx;
    std::condition_variable cv;
    int value;

public:
    Semaphore(int initial);
    void wait();
    void release();
};

#endif