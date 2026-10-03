#include "AnalyticsEngine.h"

using namespace std;

AnalyticsEngine::AnalyticsEngine() {
}

double AnalyticsEngine::calculateAveragePower(
    double energyKWh,
    double elapsedSeconds) const {

    if (elapsedSeconds <= 0) {
        return 0.0;
    }

    // 1 kWh = 3,600,000 Joules
    // Power (W) = Energy (kWh) × 3,600,000 / Time (seconds)

    return (energyKWh * 3600000.0) / elapsedSeconds;

}
