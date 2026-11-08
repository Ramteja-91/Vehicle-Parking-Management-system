#include "Bike.h"
using namespace std;

string Bike::getVehicleType() const { return "Bike"; }
double Bike::calculateFee(int parkedHours) const { return parkedHours * 20.0; }
