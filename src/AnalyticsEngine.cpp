#include "AnalyticsEngine.h"

AnalyticsEngine::AnalyticsEngine() {
}

double AnalyticsEngine::calculateAveragePower(double energyKWh,double timeHours) const {

    if (timeHours <= 0) {
        return 0.0;
    }

    return energyKWh / timeHours;
}

bool AnalyticsEngine::isHighConsumption(double energyKWh,double thresholdKWh) const {

    return energyKWh > thresholdKWh;
}

const char* AnalyticsEngine::getConsumptionStatus(double energyKWh,double thresholdKWh) const {

    if (isHighConsumption(energyKWh, thresholdKWh)) {
        return "HIGH";
    }

    return "NORMAL";
}
