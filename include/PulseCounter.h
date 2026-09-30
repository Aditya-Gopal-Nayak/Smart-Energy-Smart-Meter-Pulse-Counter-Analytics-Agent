#ifndef PULSE_COUNTER_H
#define PULSE_COUNTER_H

#include "DeviceDriver.h"

class PulseCounter {
private:
    DeviceDriver& driver;

public:
    explicit PulseCounter(DeviceDriver& device);

    unsigned long long getCount() const;
    void reset();
};

#endif
