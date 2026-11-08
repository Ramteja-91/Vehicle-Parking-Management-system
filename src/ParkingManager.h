#ifndef PARKING_MANAGER_H
#define PARKING_MANAGER_H

#include "ParkingLot.h"
#include <string>
#include <memory>

using namespace std;

class ParkingManager 
{
    private:
    ParkingLot parkingLot;
    string activeFile;
    string historyFile;

    void saveActiveVehicles() const;
    void loadActiveVehicles();
    void appendHistory(const Vehicle& vehicle, int hours, double fee) const;
    unique_ptr<Vehicle> createVehicle(const string& type,
                                           const string& number,
                                           const string& owner,
                                           time_t entry,
                                           int slot) const;

    public:
    explicit ParkingManager(int capacity = 10);
    void parkVehicle();
    void removeVehicle();
    void searchVehicle() const;
    void displayParkedVehicles() const;
    void displaySlotStatus() const;
    void displayParkingHistory() const;
};

#endif
