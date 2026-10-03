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

    int simulatedPulses;
    double measurementTimeHours;

    // Meter configuration
    const double electricityRate = 8.0;   // ₹8 per kWh

    cout << "========================================\n";
    cout << "          SMART ENERGY METER\n";
    cout << "========================================\n";

    cout << "\nEnter number of pulses: ";
    cin >> simulatedPulses;

    cout << "Enter measurement time (hours): ";
    cin >> measurementTimeHours;

    // Validate input
    if (simulatedPulses <= 0 || measurementTimeHours <= 0) {
        cout << "\nError: Please enter valid positive values.\n";
        return 1;
    }

    cout << "\nSimulating meter operation...\n";

    // Generate pulses
    generator.generateMultiplePulses(simulatedPulses);

    // Read pulse count
    unsigned long long totalPulses = counter.getCount();

    // Calculate energy
    double energy =
        energyCalculator.calculateEnergy(totalPulses);

    // Convert hours to seconds
    double elapsedSeconds = measurementTimeHours * 3600.0;

    // Calculate average power in Watts
    double averagePower = analytics.calculateAveragePower(energy,elapsedSeconds);

    // Calculate estimated cost
    double estimatedCost = energy * electricityRate;

    cout << "\n";
    cout << "----------------------------------------\n";
    cout << "           METER ANALYTICS\n";
    cout << "----------------------------------------\n";

    cout << "Total Pulses       : "
         << totalPulses << endl;

    cout << fixed << setprecision(3);

    cout << "Energy Consumed    : "
         << energy << " kWh" << endl;

    cout << fixed << setprecision(2);

    cout << "Measurement Time   : "
         << measurementTimeHours << " hours" << endl;

    cout << "Average Power      : "
         << averagePower << " W" << endl;

    cout << "Electricity Rate   : ₹"
         << electricityRate << " / kWh" << endl;

    cout << "Estimated Cost     : ₹"
         << estimatedCost << endl;

    // Save reading
    logger.logReading(
        totalPulses,
        energy,
        averagePower
    );

    cout << "Reading saved to   : logs/meter.log\n";
    cout << "System Status      : RUNNING\n";

    cout << "========================================\n";

    return 0;
}
