#ifndef TRUCK_DRIVER_H
#define TRUCK_DRIVER_H

#include <thread>
#include <random>
#include <memory>
#include "Plant.h"
#include <string>

#define LOAD_TIME 2
#define UNLOAD_TIME 2
#define REFUEL_TIME 1

class TruckDriver
{
public:
    TruckDriver(int id, Plant &tapiales, Plant &fernandez, Semaphore &mutex, int &trips);
    void start();
    void wait();
    int totalTime = 0;

private:
    int id;
    int travelTime;
    std::thread threadObj;
    Plant &tapialesPlant;
    Plant &fernandezPlant;
    Semaphore &tripsMutex;
    int &availableTrips;

    void routine();
    int generateTravelTime(int min, int max);
    void startTrip(std::string destination);
    void load(Plant &plant);
    void unload(Plant &plant);
    void refuel(Plant &plant);
    void print(Plant &plant, std::string message);
};

#endif