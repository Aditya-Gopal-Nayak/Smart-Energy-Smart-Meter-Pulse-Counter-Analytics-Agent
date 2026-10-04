# 💻 Stage 4 -- Initial Implementation & Prototype

## Smart Energy Smart-Meter Pulse Counter & Analytics Agent

### 1. Stage Objective

Implement the core modules, integrate them progressively, and
demonstrate the initial working prototype.

### 2. Implementation Order

1.  DeviceDriver
2.  PulseGenerator
3.  PulseCounter
4.  EnergyCalculator
5.  AnalyticsEngine
6.  Logger
7.  main.cpp
8.  Makefile

### 3. DeviceDriver

The user-space DeviceDriver maintains the simulated pulse count.

``` text
handlePulse() → increment pulseCount
readPulseCount() → return current count
reset() → set pulseCount to zero
```

### 4. Pulse Generation

`PulseGenerator` creates one or multiple pulses and forwards them to:

``` cpp
driver.handlePulse();
```

### 5. Pulse Counting

`PulseCounter` retrieves the accumulated count through:

``` cpp
driver.readPulseCount();
```

### 6. Energy Calculation

Meter constant:

``` text
1000 pulses = 1 kWh
Energy (kWh) = Pulses / 1000
```

Example:

``` text
100 / 1000 = 0.100 kWh
```

### 7. Power Analytics

``` text
seconds = hours × 3600
Power (W) = Energy (kWh) × 3,600,000 / seconds
```

Example:

``` text
0.100 kWh over 1 hour = 100.00 W
```

### 8. Cost Calculation

``` text
Cost = Energy × ₹8
```

Example:

``` text
0.100 × ₹8 = ₹0.80
```

### 9. Logging

Readings are stored in:

``` text
logs/meter.log
```

### 10. Build System

``` bash
make
./smart_meter
make clean
```

### 11. Prototype Workflow

``` text
User Input
 → Pulse Generator
 → DeviceDriver
 → PulseCounter
 → EnergyCalculator
 → AnalyticsEngine
 → Cost Calculation
 → Logger
```

### 12. Demonstration Output

``` text
========================================
          SMART ENERGY METER
========================================

Enter number of pulses: 100
Enter measurement time (hours): 1

Simulating meter operation...

----------------------------------------
           METER ANALYTICS
----------------------------------------
Total Pulses       : 100
Energy Consumed    : 0.100 kWh
Measurement Time   : 1.00 hours
Average Power      : 100.00 W
Electricity Rate   : ₹8.00 / kWh
Estimated Cost     : ₹0.80
Reading saved to   : logs/meter.log
System Status      : RUNNING
========================================
```

### 13. Integration

`main.cpp` creates the modules, accepts input, generates pulses,
calculates energy/power/cost, and saves the result.

### 14. Issues and Solutions

-   **Invalid input:** solved with positive-value validation.
-   **Invalid time:** AnalyticsEngine handles non-positive elapsed time.
-   **Invalid meter constant:** EnergyCalculator prevents invalid
    division.
-   **Log failure:** Logger checks file opening.

Only document issues that actually occurred during development.

### 15. Stage Deliverables

-   Core C++ modules
-   Working prototype
-   Integrated application
-   Makefile
-   Terminal output
-   Log output

### 16. Progress Evidence

Source commits, compilation output, screenshots, terminal output, log
output, and issue/resolution notes.

### 17. Git Commit

``` bash
git add .
git commit -m "feat: implement initial smart meter prototype"
git push origin main
```

### 18. Next Stage

**Stage 5 -- Testing, Integration & Improvement**
