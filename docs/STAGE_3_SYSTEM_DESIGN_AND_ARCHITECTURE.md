# 🏗️ Stage 3 -- System Design & Architecture

## Smart Energy Smart-Meter Pulse Counter & Analytics Agent

### 1. Stage Objective

Define the complete architecture, component responsibilities, data
structures, UML diagrams, implementation plan, development environment,
and Git workflow.

### 2. High-Level Architecture

``` text
User Input
    |
    v
Pulse Generator
    |
    v
DeviceDriver (User-Space Simulation)
    |
    v
Pulse Counter
    |
    v
Energy Calculator
    |
    v
Analytics Engine
    |
    +---- Energy (kWh)
    +---- Power (W)
    |
    v
Cost Calculation
    |
    v
Logger
    |
    v
logs/meter.log
```

> The current DeviceDriver is a C++ user-space simulation, not a Linux
> kernel module.

### 3. Component Responsibilities

-   **PulseGenerator:** Creates simulated pulses.
-   **DeviceDriver:** Receives pulses and maintains the count.
-   **PulseCounter:** Reads and resets the count.
-   **EnergyCalculator:** Converts pulses to kWh.
-   **AnalyticsEngine:** Calculates average power.
-   **Cost Calculation:** Estimates electricity cost.
-   **Logger:** Stores readings.
-   **main.cpp:** Coordinates the workflow.

### 4. Data Flow

``` text
User Input → Pulse Generation → DeviceDriver → Pulse Counter → Energy Calculation → Power Analytics → Cost Calculation → Logger
```

### 5. Data Structures

``` cpp
unsigned long long pulseCount;
double pulsesPerKWh;
int simulatedPulses;
double measurementTimeHours;
double energy;
double elapsedSeconds;
double averagePower;
double estimatedCost;
```

### 6. UML Diagrams

**Class Diagram:** PulseGenerator, DeviceDriver, PulseCounter,
EnergyCalculator, AnalyticsEngine, Logger.

**Sequence Diagram:**

``` text
User → main → PulseGenerator → DeviceDriver
                         ↓
                  PulseCounter
                         ↓
                EnergyCalculator
                         ↓
                AnalyticsEngine
                         ↓
                      Logger
```

**State Machine:**

``` text
START → INPUT → VALIDATE
          |         |
          |         +--> ERROR
          v
     GENERATE PULSES
          ↓
     COUNT PULSES
          ↓
       CALCULATE
          ↓
      LOG READING
          ↓
       COMPLETE
```

### 7. Implementation Plan

1.  Create structure.
2.  Implement DeviceDriver.
3.  Implement PulseGenerator.
4.  Implement PulseCounter.
5.  Implement EnergyCalculator.
6.  Implement AnalyticsEngine.
7.  Implement Logger.
8.  Integrate `main.cpp`.
9.  Create Makefile.
10. Compile, test, and document.

### 8. Development Environment

-   Operating System: Linux
-   Compiler: g++
-   Standard: C++17
-   Build: Makefile
-   Version Control: Git/GitHub
-   Editor: Nano or compatible editor

### 9. Git Strategy

Use meaningful commits such as:

``` text
feat:
fix:
test:
docs:
refactor:
```

Examples:

``` bash
git commit -m "feat: implement pulse generator"
git commit -m "feat: add energy calculation"
git commit -m "test: validate meter calculations"
git commit -m "docs: update architecture"
```

### 10. Stage Deliverables

-   Architecture
-   Data flow
-   Component responsibilities
-   Data structures
-   Class Diagram
-   Sequence Diagram
-   State Machine Diagram
-   Implementation plan
-   Development environment
-   Git configuration

### 11. Progress Evidence

Architecture diagram, UML files, repository, source structure,
environment screenshots, and commit history.

### 12. Git Commit

``` bash
git add .
git commit -m "docs: complete stage 3 system design and architecture"
git push origin main
```

### 13. Next Stage

**Stage 4 -- Initial Implementation & Prototype**
