#include "src/ParkingManager.h"
#include <iostream>
#include <limits>

using namespace std;

// Create a parking manager with 10 parking slots.
int main() 
{
    ParkingManager manager(10);
    int choice = 0;

    cout << "============================================\n";
    cout << "       VEHICLE PARKING MANAGEMENT SYSTEM\n";
    cout << "============================================\n";

    // Keep showing the menu until the user selects Exit.
    do 
    {
        cout << "\n--------------- MAIN MENU ----------------\n"
                  << "1. Park a vehicle\n"
                  << "2. Vehicle exit and generate bill\n"
                  << "3. Search for a vehicle\n"
                  << "4. Display all parked vehicles\n"
                  << "5. Display parking slot status\n"
                  << "6. View parking history\n"
                  << "7. Exit\n"
                  << "-------------------------------------------\n"
                  << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid number.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Call the function that matches the selected menu option.
        switch (choice) 
        {
            case 1: manager.parkVehicle(); break;
            case 2: manager.removeVehicle(); break;
            case 3: manager.searchVehicle(); break;
            case 4: manager.displayParkedVehicles(); break;
            case 5: manager.displaySlotStatus(); break;
            case 6: manager.displayParkingHistory(); break;
            case 7: cout << "\nThank you for using the parking system.\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
