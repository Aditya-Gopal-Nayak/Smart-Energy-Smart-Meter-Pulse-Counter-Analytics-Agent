#ifndef DEVICE_DRIVER_H
#define DEVICE_DRIVER_H

class DeviceDriver {
private:
    unsigned long long pulseCount;

public:
    DeviceDriver();

    void handlePulse();
    unsigned long long readPulseCount() const;
    void reset();
};

#endif
