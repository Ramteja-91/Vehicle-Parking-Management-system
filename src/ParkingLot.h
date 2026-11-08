#ifndef PARKING_LOT_H
#define PARKING_LOT_H

#include "Vehicle.h"
#include <memory>
#include <vector>
#include <string>

using namespace std;

class ParkingLot 
{
    private:
    int capacity;
    vector<unique_ptr<Vehicle>> parkedVehicles;

    public:
    explicit ParkingLot(int totalSlots);
    int getCapacity() const;
    int getAvailableSlots() const;
    int findAvailableSlot() const;
    bool isVehicleParked(const string& number) const;
    bool addVehicle(unique_ptr<Vehicle> vehicle);
    unique_ptr<Vehicle> removeVehicle(const string& number);
    Vehicle* findVehicle(const string& number) const;
    const vector<unique_ptr<Vehicle>>& getParkedVehicles() const;
};

#endif
