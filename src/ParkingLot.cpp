#include "ParkingLot.h"
#include <algorithm>

using namespace std;

ParkingLot::ParkingLot(int totalSlots) : capacity(totalSlots) {}

int ParkingLot::getCapacity() const { return capacity; }

int ParkingLot::getAvailableSlots() const 
{
    return capacity - static_cast<int>(parkedVehicles.size());
}

int ParkingLot::findAvailableSlot() const 
{
    for (int slot = 1; slot <= capacity; ++slot) 
    {
        bool occupied = false;
        for (const auto& vehicle : parkedVehicles) 
        {
            if (vehicle->getSlotNumber() == slot) 
            {
                occupied = true;
                break;
            }
        }
        if (!occupied) return slot;
    }
    return -1;
}

bool ParkingLot::isVehicleParked(const string& number) const 
{
    return findVehicle(number) != nullptr;
}

bool ParkingLot::addVehicle(unique_ptr<Vehicle> vehicle) 
{
    if (!vehicle || getAvailableSlots() <= 0 ||
        isVehicleParked(vehicle->getVehicleNumber())) 
        {
        return false;
    }
    parkedVehicles.push_back(move(vehicle));
    return true;
}

unique_ptr<Vehicle> ParkingLot::removeVehicle(const string& number) 
{
    for (auto it = parkedVehicles.begin(); it != parkedVehicles.end(); ++it) 
    {
        if ((*it)->getVehicleNumber() == number) 
        {
            unique_ptr<Vehicle> removed = move(*it);
            parkedVehicles.erase(it);
            return removed;
        }
    }
    return nullptr;
}

Vehicle* ParkingLot::findVehicle(const string& number) const 
{
    for (const auto& vehicle : parkedVehicles) 
    {
        if (vehicle->getVehicleNumber() == number) return vehicle.get();
    }
    return nullptr;
}

const vector<unique_ptr<Vehicle>>& ParkingLot::getParkedVehicles() const 
{
    return parkedVehicles;
}
