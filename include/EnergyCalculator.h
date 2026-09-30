#ifndef ENERGY_CALCULATOR_H
#define ENERGY_CALCULATOR_H

class EnergyCalculator {
private:
    double pulsesPerKWh;

public:
    explicit EnergyCalculator(double pulsesPerKWh = 1000.0);

    double calculateEnergy(unsigned long long pulseCount) const;
};

#endif
