#include "TruckDriver.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

#define MIN_TRAVEL_TIME 18
#define MAX_TRAVEL_TIME 24

TruckDriver::TruckDriver(int id, Plant &tapiales, Plant &fernandez, Semaphore &mutex, int &trips)
    : id(id), tapialesPlant(tapiales), fernandezPlant(fernandez), tripsMutex(mutex), availableTrips(trips)
{
    travelTime = generateTravelTime(MIN_TRAVEL_TIME, MAX_TRAVEL_TIME);
}

void TruckDriver::start()
{
    threadObj = thread(&TruckDriver::routine, this);
}

void TruckDriver::wait()
{
    if (threadObj.joinable())
    {
        threadObj.join();
    }
}

int TruckDriver::generateTravelTime(int min, int max)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void TruckDriver::routine()
{
    tripsMutex.wait();
    while (availableTrips > 0)
    {
        availableTrips--;
        tripsMutex.release();
        load(tapialesPlant);
        startTrip("Fernandez");
        unload(fernandezPlant);
        load(fernandezPlant);
        refuel(fernandezPlant);
        startTrip("Tapiales");
        unload(tapialesPlant);
        tripsMutex.wait();
    }
    tripsMutex.release();
    std::string message = "TruckDriver " + std::to_string(id) + " has finished their shift in " + std::to_string(travelTime) + "hs.\n";
    std::cout << message;
}

void TruckDriver::startTrip(std::string destination)
{
    std::string message = "TruckDriver " + std::to_string(id) + " traveling to " + destination + ", Travel time: " + std::to_string(travelTime) + "hs.\n";
    std::cout << message;
    totalTime += travelTime;
    this_thread::sleep_for(chrono::milliseconds(travelTime));
}

void TruckDriver::load(Plant &plant)
{
    print(plant, "Waiting to load");
    auto attempt = std::chrono::steady_clock::now();
    plant.loadSemaphore.wait();
    auto entry = std::chrono::steady_clock::now();

    print(plant, "Loading");
    this_thread::sleep_for(chrono::milliseconds(LOAD_TIME));
    print(plant, "Load complete");
    plant.loadSemaphore.release();

    auto waitTime = std::chrono::duration_cast<std::chrono::milliseconds>(entry - attempt).count();
    totalTime += LOAD_TIME + waitTime;
}

void TruckDriver::unload(Plant &plant)
{
    print(plant, "Waiting to unload");
    auto attempt = std::chrono::steady_clock::now();
    plant.unloadSemaphore.wait();
    auto entry = std::chrono::steady_clock::now();

    print(plant, "Unloading");
    this_thread::sleep_for(chrono::milliseconds(UNLOAD_TIME));
    print(plant, "Unload complete");
    plant.unloadSemaphore.release();

    auto waitTime = std::chrono::duration_cast<std::chrono::milliseconds>(entry - attempt).count();
    totalTime += UNLOAD_TIME + waitTime;
}

void TruckDriver::refuel(Plant &plant)
{
    print(plant, "Waiting to refuel");
    auto attempt = std::chrono::steady_clock::now();
    plant.fuelSemaphore.wait();
    auto entry = std::chrono::steady_clock::now();

    print(plant, "Refueling");
    this_thread::sleep_for(chrono::milliseconds(REFUEL_TIME));
    print(plant, "Refuel complete");
    plant.fuelSemaphore.release();

    auto waitTime = std::chrono::duration_cast<std::chrono::milliseconds>(entry - attempt).count();
    totalTime += REFUEL_TIME + waitTime;
}

void TruckDriver::print(Plant &plant, std::string action)
{
    std::string message = "TruckDriver " + std::to_string(id) + " at plant " + plant.name + ": " + action + ".\n";
    std::cout << message;
}
