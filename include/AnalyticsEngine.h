#ifndef ANALYTICS_ENGINE_H
#define ANALYTICS_ENGINE_H

class AnalyticsEngine {
public:
    AnalyticsEngine();

    double calculateAveragePower(double energyKWh,double timeHours) const;

    bool isHighConsumption(double energyKWh,double thresholdKWh) const;

    const char* getConsumptionStatus(double energyKWh,double thresholdKWh) const;
};

#endif
