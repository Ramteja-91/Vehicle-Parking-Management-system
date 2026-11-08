#include "Car.h"
using namespace std;

string Car::getVehicleType() const { return "Car"; }
double Car::calculateFee(int parkedHours) const { return parkedHours * 40.0; }
