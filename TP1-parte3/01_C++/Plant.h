#ifndef PLANT_H
#define PLANT_H

#include "Semaphore.h"
#include <string>

class Plant
{
public:
    std::string name;
    Semaphore loadSemaphore;
    Semaphore unloadSemaphore;
    Semaphore fuelSemaphore;
    Plant(std::string plantName);
};

#endif