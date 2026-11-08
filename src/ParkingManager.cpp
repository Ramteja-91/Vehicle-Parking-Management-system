#include "ParkingManager.h"
#include "Car.h"
#include "Bike.h"
#include "Truck.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <algorithm>
#include <cmath>
#include <ctime>

using namespace std;

namespace 
{
    string cleanField(string value) 
{
    value.erase(remove(value.begin(), value.end(), '|'), value.end());
    return value;
}

string formatTime(time_t value) 
{
    tm* timeInfo = localtime(&value);
    char buffer[30] = "Unknown";
    if (timeInfo) strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M %p", timeInfo);
    return buffer;
}
}

ParkingManager::ParkingManager(int capacity)
    : parkingLot(capacity),
      activeFile("data/active_vehicles.txt"),
      historyFile("data/parking_history.txt") 
{
    filesystem::create_directories("data");
    loadActiveVehicles();
}

unique_ptr<Vehicle> ParkingManager::createVehicle(
    const string& type, const string& number,
    const string& owner, time_t entry, int slot) const 
{
    if (type == "Car") return make_unique<Car>(number, owner, entry, slot);
    if (type == "Bike") return make_unique<Bike>(number, owner, entry, slot);
    if (type == "Truck") return make_unique<Truck>(number, owner, entry, slot);
    return nullptr;
}

void ParkingManager::loadActiveVehicles() 
{
    ifstream file(activeFile);
    if (!file) return;

    string line;
    while (getline(file, line)) 
    {
        stringstream ss(line);
        string type, number, owner, entryText, slotText;
        if (!getline(ss, type, '|') ||
            !getline(ss, number, '|') ||
            !getline(ss, owner, '|') ||
            !getline(ss, entryText, '|') ||
            !getline(ss, slotText, '|')) continue;

        try 
        {
            time_t entry = static_cast<time_t>(stoll(entryText));
            int slot = stoi(slotText);
            if (slot < 1 || slot > parkingLot.getCapacity() ||
                parkingLot.isVehicleParked(number)) continue;

            auto vehicle = createVehicle(type, number, owner, entry, slot);
            if (vehicle) parkingLot.addVehicle(move(vehicle));
        } catch (...) 
        {
            // Ignore malformed records and continue loading valid records.
        }
    }
}

void ParkingManager::saveActiveVehicles() const 
{
    ofstream file(activeFile, ios::trunc);
    if (!file) 
    {
        cout << "Warning: Could not save active parking records.\n";
        return;
    }
    for (const auto& vehicle : parkingLot.getParkedVehicles()) 
    {
        file << vehicle->getVehicleType() << '|'
             << cleanField(vehicle->getVehicleNumber()) << '|'
             << cleanField(vehicle->getOwnerName()) << '|'
             << static_cast<long long>(vehicle->getEntryTime()) << '|'
             << vehicle->getSlotNumber() << '\n';
    }
}

void ParkingManager::appendHistory(const Vehicle& vehicle, int hours, double fee) const 
{
   ofstream file(historyFile, ios::app);
    if (!file) 
    {
        cout << "Warning: Could not update parking history.\n";
        return;
    }
    file << vehicle.getVehicleType() << '|'
         << cleanField(vehicle.getVehicleNumber()) << '|'
         << cleanField(vehicle.getOwnerName()) << '|'
         << vehicle.getSlotNumber() << '|'
         << formatTime(vehicle.getEntryTime()) << '|'
         << formatTime(time(nullptr)) << '|'
         << hours << '|'
         << fixed << setprecision(2) << fee << '\n';
}

void ParkingManager::parkVehicle() 
{
    if (parkingLot.getAvailableSlots() == 0) 
    {
        cout << "\nSorry, the parking lot is full.\n";
        return;
    }

    string number, owner;
    int choice;
    cout << "\nVehicle type (1. Car  2. Bike  3. Truck): ";
    if (!(cin >> choice)) 
    {
        cin.clear(); cin.ignore(10000, '\n');
        cout << "Invalid input.\n"; return;
    }
    cin.ignore(10000, '\n');

    string type;
    if (choice == 1) type = "Car";
    else if (choice == 2) type = "Bike";
    else if (choice == 3) type = "Truck";
    else { cout << "Invalid vehicle type.\n"; return; }

    cout << "Enter vehicle registration number: ";
    getline(cin, number);
    cout << "Enter owner name: ";
    getline(cin, owner);

    number = cleanField(number);
    owner = cleanField(owner);
    if (number.empty() || owner.empty()) 
    {
        cout << "Vehicle number and owner name cannot be empty.\n";
        return;
    }
    if (parkingLot.isVehicleParked(number)) 
    {
        cout << "This vehicle is already parked.\n";
        return;
    }

    int slot = parkingLot.findAvailableSlot();
    auto vehicle = createVehicle(type, number, owner, time(nullptr), slot);
    if (parkingLot.addVehicle(move(vehicle))) 
    {
        saveActiveVehicles();
        cout << "\nVehicle parked successfully. Allocated slot: " << slot << "\n";
    } else 
    {
        cout << "Unable to park vehicle.\n";
    }
}

void ParkingManager::removeVehicle() 
{
    string number;
    cout << "\nEnter vehicle registration number to exit: ";
    getline(cin >> ws, number);

    auto vehicle = parkingLot.removeVehicle(number);
    if (!vehicle) 
    {
        cout << "Vehicle not found in the parking lot.\n";
        return;
    }

    const time_t now = time(nullptr);
    const double seconds = difftime(now, vehicle->getEntryTime());
    const int hours = max(1, static_cast<int>(ceil(seconds / 3600.0)));
    const double fee = vehicle->calculateFee(hours);

    cout << "\n========== PARKING BILL ==========\n"
              << "Vehicle type : " << vehicle->getVehicleType() << '\n'
              << "Vehicle no.  : " << vehicle->getVehicleNumber() << '\n'
              << "Owner        : " << vehicle->getOwnerName() << '\n'
              << "Slot number  : " << vehicle->getSlotNumber() << '\n'
              << "Entry time   : " << formatTime(vehicle->getEntryTime()) << '\n'
              << "Exit time    : " << formatTime(now) << '\n'
              << "Parked hours : " << hours << '\n'
              << "Total fee    : Rs. " << fixed << setprecision(2) << fee << '\n'
              << "==================================\n";

    appendHistory(*vehicle, hours, fee);
    saveActiveVehicles();
}

void ParkingManager::searchVehicle() const 
{
    string number;
    cout << "\nEnter vehicle registration number: ";
    getline(cin >> ws, number);

    Vehicle* vehicle = parkingLot.findVehicle(number);
    if (!vehicle) 
    {
        cout << "Vehicle is not currently parked.\n";
        return;
    }

    cout << "\nType        Number          Owner                 Slot      Entry time\n";
    vehicle->displayDetails();
}

void ParkingManager::displayParkedVehicles() const 
{
    const auto& vehicles = parkingLot.getParkedVehicles();
    if (vehicles.empty()) 
    {
        cout << "\nNo vehicles are currently parked.\n";
        return;
    }

    cout << "\nType        Number          Owner                 Slot      Entry time\n";
    cout << "--------------------------------------------------------------------------\n";
    for (const auto& vehicle : vehicles) vehicle->displayDetails();
    cout << "\nTotal parked: " << vehicles.size() << '\n';
}

void ParkingManager::displaySlotStatus() const 
{
    cout << "\n========== PARKING SLOT STATUS ==========\n";
    for (int slot = 1; slot <= parkingLot.getCapacity(); ++slot) 
    {
        bool occupied = false;
        string number;
        for (const auto& vehicle : parkingLot.getParkedVehicles()) 
        {
            if (vehicle->getSlotNumber() == slot) 
            {
                occupied = true;
                number = vehicle->getVehicleNumber();
                break;
            }
        }
        cout << "Slot " << setw(2) << slot << " : "
                  << (occupied ? "Occupied (" + number + ")" : "Available") << '\n';
    }
    cout << "Available slots: " << parkingLot.getAvailableSlots()
              << " / " << parkingLot.getCapacity() << '\n';
}

void ParkingManager::displayParkingHistory() const 
{
    ifstream file(historyFile);
    if (!file) 
    {
        cout << "\nNo parking history available yet.\n";
        return;
    }

    cout << "\n================ PARKING HISTORY ================\n";
    cout << "Type | Vehicle No | Owner | Slot | Entry | Exit | Hours | Fee (Rs.)\n";
    string line;
    bool hasRecords = false;
    while (getline(file, line)) 
    {
        if (!line.empty()) 
        {
            cout << line << '\n';
            hasRecords = true;
        }
    }
    if (!hasRecords) cout << "No completed parking records found.\n";
}
