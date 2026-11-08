#include "Truck.h"
using namespace std;

string Truck::getVehicleType() const { return "Truck"; }
double Truck::calculateFee(int parkedHours) const { return parkedHours * 60.0; }
