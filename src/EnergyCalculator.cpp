#include "EnergyCalculator.h"

using namespace std;

EnergyCalculator::EnergyCalculator(double pulsesPerKWh)
    : pulsesPerKWh(pulsesPerKWh) {
}

double EnergyCalculator::calculateEnergy(
    unsigned long long pulseCount) const {

    if (pulsesPerKWh <= 0) {
        return 0.0;
    }

    return static_cast<double>(pulseCount) / pulsesPerKWh;
}
