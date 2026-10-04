# 📋 Stage 2 -- Project Requirements & Development Plan

## Smart Energy Smart-Meter Pulse Counter & Analytics Agent

### 1. Stage Objective

Define functional and non-functional requirements, PRD, modules,
features, deliverables, and development plan.

### 2. Functional Requirements

-   **FR-01:** Accept simulated pulse count.
-   **FR-02:** Accept measurement time in hours.
-   **FR-03:** Generate the requested number of pulses.
-   **FR-04:** Process pulses through the user-space DeviceDriver.
-   **FR-05:** Maintain and retrieve pulse count.
-   **FR-06:** Calculate energy using `Energy = Pulses / 1000`.
-   **FR-07:** Calculate power using
    `Power = Energy × 3,600,000 / seconds`.
-   **FR-08:** Calculate cost using `Cost = Energy × ₹8`.
-   **FR-09:** Display meter analytics.
-   **FR-10:** Save readings to `logs/meter.log`.
-   **FR-11:** Reject non-positive input.

### 3. Non-Functional Requirements

-   Linux operating environment.
-   C++17 implementation.
-   Modular architecture.
-   Maintainable source structure.
-   Input and calculation validation.
-   Clear documentation.
-   Git/GitHub version control.

### 4. Modules

  Module             Responsibility
  ------------------ -------------------------------
  PulseGenerator     Generates simulated pulses
  DeviceDriver       User-space device abstraction
  PulseCounter       Reads/resets pulse count
  EnergyCalculator   Converts pulses to kWh
  AnalyticsEngine    Calculates average power
  Cost Calculation   Estimates electricity cost
  Logger             Stores readings
  main.cpp           Application orchestration

### 5. PRD

**Product:** Smart Energy Smart-Meter Pulse Counter & Analytics Agent\
**Platform:** Linux\
**Language:** C++17\
**Compiler:** g++\
**Build:** Makefile\
**Version Control:** Git/GitHub\
**Primary User:** Student/trainer evaluating Linux, C++, system
programming, and device-driver concepts.

### 6. Features

-   Pulse generation
-   Pulse counting
-   Device abstraction
-   Energy calculation
-   Power analytics
-   Cost estimation
-   Logging
-   Input validation
-   Modular source structure
-   Makefile build

### 7. Deliverables

1.  Source code
2.  Header files
3.  Makefile
4.  README
5.  Six stage documents
6.  Project report
7.  UML diagrams
8.  Test results
9.  Log output
10. GitHub repository

### 8. Development Plan

  Stage   Activity
  ------- -------------------------------------
  1       Project Introduction
  2       Requirements & Development Plan
  3       System Design & Architecture
  4       Initial Implementation & Prototype
  5       Testing, Integration & Improvement
  6       Final Implementation & Presentation

### 9. Progress Evidence

Maintain PRD, requirements checklist, module planning, Git commits,
development notes, and setup screenshots.

### 10. Demonstration

Explain functional requirements, non-functional requirements, modules,
deliverables, and roadmap.

### 11. Git Commit

``` bash
git add .
git commit -m "docs: complete stage 2 requirements and development plan"
git push origin main
```

### 12. Next Stage

**Stage 3 -- System Design & Architecture**
