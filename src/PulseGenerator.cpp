#include "PulseGenerator.h"

PulseGenerator::PulseGenerator(DeviceDriver& device)
    : driver(device) {
}

void PulseGenerator::generatePulse() {
    driver.handlePulse();
}

void PulseGenerator::generateMultiplePulses(int numberOfPulses) {
    if (numberOfPulses <= 0) {
        return;
    }

    for (int i = 0; i < numberOfPulses; i++) {
        generatePulse();
    }
}
