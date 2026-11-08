#ifndef CAR_H
#define CAR_H
#include "Vehicle.h"

using namespace std;

class Car : public Vehicle 
{
    public:
    using Vehicle::Vehicle;
    string getVehicleType() const override;
    double calculateFee(int parkedHours) const override;
};
#endif
