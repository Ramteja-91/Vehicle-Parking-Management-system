#include "Vehicle.h"
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

Vehicle::Vehicle(const string& number,
                 const string& owner,
                 time_t entry,
                 int slot)
    : vehicleNumber(number), ownerName(owner), entryTime(entry), slotNumber(slot) {}

string Vehicle::getVehicleNumber() const { return vehicleNumber; }
string Vehicle::getOwnerName() const { return ownerName; }
time_t Vehicle::getEntryTime() const { return entryTime; }
int Vehicle::getSlotNumber() const { return slotNumber; }

void Vehicle::displayDetails() const 
{
    tm* timeInfo = localtime(&entryTime);
    char timeBuffer[30] = "Unknown";
    if (timeInfo) {
        strftime(timeBuffer, sizeof(timeBuffer), "%d-%m-%Y %I:%M:%S %p", timeInfo);
    }

    cout << left
              << setw(12) << getVehicleType()
              << setw(16) << vehicleNumber
              << setw(22) << ownerName
              << setw(10) << slotNumber
              << timeBuffer << '\n';
}
