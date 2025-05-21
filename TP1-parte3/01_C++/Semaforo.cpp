#include "Semaforo.h"

Semaforo::Semaforo(int inicial) : valor(inicial) {}

void Semaforo::esperar()
{
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this]()
            { return valor > 0; });
    --valor;
}

void Semaforo::liberar()
{
    std::unique_lock<std::mutex> lock(mtx);
    ++valor;
    cv.notify_one();
}
