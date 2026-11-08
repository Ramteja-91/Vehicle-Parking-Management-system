#ifndef TRUCK_H
#define TRUCK_H
#include "Vehicle.h"

using namespace std;

class Truck : public Vehicle 
{
    public:
    using Vehicle::Vehicle;
    string getVehicleType() const override;
    double calculateFee(int parkedHours) const override;
};
#endif
