#ifndef ANALYTICS_ENGINE_H
#define ANALYTICS_ENGINE_H

class AnalyticsEngine {
public:
    AnalyticsEngine();

    double calculateAveragePower(double energyKWh,double elapsedSeconds) const;

};

#endif
