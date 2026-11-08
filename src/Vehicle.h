#ifndef VEHICLE_H
#define VEHICLE_H

#include <ctime>
#include <string>

using namespace std;

class Vehicle 
{
    private:
    string vehicleNumber;
    string ownerName;
    time_t entryTime;
    int slotNumber;

    public:
    Vehicle(const string& number,
            const string& owner,
            time_t entry,
            int slot);
    virtual ~Vehicle() = default;

    string getVehicleNumber() const;
    string getOwnerName() const;
    time_t getEntryTime() const;
    int getSlotNumber() const;

    virtual string getVehicleType() const = 0;
    virtual double calculateFee(int parkedHours) const = 0;

    void displayDetails() const;
};

#endif
