#include "PulseCounter.h"

PulseCounter::PulseCounter(DeviceDriver& device)
    : driver(device) {
}

unsigned long long PulseCounter::getCount() const {
    return driver.readPulseCount();
}

void PulseCounter::reset() {
    driver.reset();
}
