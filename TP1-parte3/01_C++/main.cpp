#include <iostream>
#include <vector>
#include "Plant.h"
#include "TruckDriver.h"

int main(int argc, char const *argv[])
{
    Plant tapiales = Plant("Tapiales");
    Plant fernandez = Plant("Fernandez");
    Semaphore tripMutex(1);
    int trips = 4;
    int drivers = 4;
    int maxTime = 0;
    std::vector<TruckDriver> truckDrivers;

    for (int i = 0; i < drivers; ++i)
    {
        truckDrivers.emplace_back(i + 1, tapiales, fernandez, tripMutex, trips);
    }

    for (auto &truckDriver : truckDrivers)
    {
        truckDriver.start();
    }

    for (auto &truckDriver : truckDrivers)
    {
        truckDriver.wait();
        maxTime = std::max(maxTime, truckDriver.totalTime);
    }

    int days = maxTime / 24;
    int hours = maxTime % 24;
    std::cout << "Total time to complete all trips: " << days << " days " << hours << " hours" << std::endl;
    return 0;
}
