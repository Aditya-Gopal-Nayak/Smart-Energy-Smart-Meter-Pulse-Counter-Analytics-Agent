#include <iostream>
#include <iomanip>

#include "DeviceDriver.h"
#include "PulseCounter.h"
#include "PulseGenerator.h"
#include "EnergyCalculator.h"
#include "AnalyticsEngine.h"
#include "Logger.h"

using namespace std;

int main() {

    DeviceDriver driver;

    PulseCounter counter(driver);
    PulseGenerator generator(driver);
    EnergyCalculator energyCalculator;
    AnalyticsEngine analytics;
    Logger logger("logs/meter.log");

    cout << "========================================\n";
    cout << "        SMART ENERGY METER\n";
    cout << "========================================\n";

    cout << "Generating 10 simulated pulses...\n";

    generator.generateMultiplePulses(3600);

    unsigned long long totalPulses = counter.getCount();

    double energy =
        energyCalculator.calculateEnergy(totalPulses);

    double timeHours = 1.0;

    double averagePower =
        analytics.calculateAveragePower(
            energy, timeHours);

    double threshold = 5.0;

    const char* status =
        analytics.getConsumptionStatus(
            energy, threshold);

    cout << fixed << setprecision(2);

    cout << "\n";
    cout << "----------------------------------------\n";
    cout << "           METER ANALYTICS\n";
    cout << "----------------------------------------\n";

    cout << "Total Pulses       : "
         << totalPulses << endl;

    cout << "Energy Consumed    : "
         << energy << " kWh" << endl;

    cout << "Average Power      : "
         << averagePower << " kW" << endl;

    cout << "Consumption Status : "
         << status << endl;

    cout << "----------------------------------------\n";

    logger.logReading(
        totalPulses,
        energy,
        averagePower,
        status
    );

    cout << "Reading saved to   : logs/meter.log\n";
    cout << "System Status      : RUNNING\n";

    cout << "========================================\n";

    return 0;
}
