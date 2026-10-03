#include "Logger.h"

#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

Logger::Logger(const string& filename) : filename(filename) {
}

void Logger::logReading(unsigned long long pulses,double energyKWh,double averagePower) {
    ofstream logFile(filename, ios::app);

    if (!logFile) {
        cerr << "Error: Unable to open log file.\n";
        return;
    }

    logFile << fixed << setprecision(2);

    logFile << "Pulses: " << pulses
            << " | Energy: " << energyKWh << " kWh"
            << " | Average Power: " << averagePower << " kW"
            << '\n';

    logFile.close();
}
