#ifndef PULSE_GENERATOR_H
#define PULSE_GENERATOR_H

#include "DeviceDriver.h"

class PulseGenerator {
private:
    DeviceDriver& driver;

public:
    explicit PulseGenerator(DeviceDriver& device);

    void generatePulse();
    void generateMultiplePulses(int numberOfPulses);
};

#endif
