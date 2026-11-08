#ifndef BIKE_H
#define BIKE_H
#include "Vehicle.h"

using namespace std;

class Bike : public Vehicle 
{
    public:
    using Vehicle::Vehicle;
    string getVehicleType() const override;
    double calculateFee(int parkedHours) const override;
};
#endif
