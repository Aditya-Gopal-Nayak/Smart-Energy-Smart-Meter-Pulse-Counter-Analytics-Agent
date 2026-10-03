#ifndef LOGGER_H
#define LOGGER_H

#include <string>

using namespace std;

class Logger {
public:
    explicit Logger(const string& filename);

    void logReading(unsigned long long pulses,
                    double energyKWh,
                    double averagePower);

private:
    string filename;
};

#endif
