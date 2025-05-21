#include "Plant.h"

#include "Plant.h"

Plant::Plant(std::string plantName)
    : name(plantName), loadSemaphore(1), unloadSemaphore(1), fuelSemaphore(2) {}
