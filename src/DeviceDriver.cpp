#include "DeviceDriver.h"

DeviceDriver::DeviceDriver() {
    pulseCount = 0;
}

void DeviceDriver::handlePulse() {
    pulseCount++;
}

unsigned long long DeviceDriver::readPulseCount() const {
    return pulseCount;
}

void DeviceDriver::reset() {
    pulseCount = 0;
}
