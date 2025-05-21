#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <mutex>
#include <condition_variable>

class Semaforo
{
private:
    std::mutex mtx;
    std::condition_variable cv;
    int valor;

public:
    Semaforo(int inicial);
    void esperar();
    void liberar();
};

#endif
