# ⚡ Smart Energy Smart-Meter Pulse Counter & Analytics Agent

**A modular, software-only smart-meter simulator written in C++17 for Linux, built around a user-space device-driver abstraction.**

| | |
|---|---|
| **Project Type** | Individual Academic Project |
| **Domain** | Linux, Device Drivers, System Programming & C++ |
| **Language / Standard** | C++17 |
| **Platform** | Linux |
| **Build System** | `g++` |
| **Author** | Aditya Gopal Nayak |

---

## 📑 Table of Contents

1. [Project Overview](#1-project-overview)
2. [Problem Statement](#2-problem-statement)
3. [Objectives](#3-objectives)
4. [Project Type](#4-project-type)
5. [Technologies Used](#5-technologies-used)
6. [System Architecture](#6-system-architecture)
7. [Data Flow](#7-data-flow)
8. [Device Driver Concept](#8-device-driver-concept)
9. [Project Structure](#9-project-structure)
10. [Module Description](#10-module-description)
11. [Configuration](#11-configuration)
12. [Requirements](#12-requirements)
13. [Build Instructions](#13-build-instructions)
14. [Run Instructions](#14-run-instructions)
15. [Example Output](#15-example-output)
16. [Example Calculations](#16-example-calculations)
17. [Testing and Validation](#17-testing-and-validation)
18. [Linux Concepts Used](#18-linux-concepts-used)
19. [C++ Concepts Used](#19-c-concepts-used)
20. [System Programming Concepts](#20-system-programming-concepts)
21. [Software Architecture Concepts](#21-software-architecture-concepts)
22. [Logging](#22-logging)
23. [Makefile Commands](#23-makefile-commands)
24. [Git and GitHub](#24-git-and-github)
25. [Project Development Stages](#25-project-development-stages)
26. [Project Scope](#26-project-scope)
27. [Limitations](#27-limitations)
28. [Future Enhancements](#28-future-enhancements)
29. [Author](#29-author)
30. [Conclusion](#30-conclusion)

---

## 1. Project Overview

The **Smart Energy Smart-Meter Pulse Counter & Analytics Agent** is a **software-only simulator** of an electricity meter. A real energy meter emits pulses in proportion to the energy consumed; this project reproduces that behaviour in software and passes the simulated pulses through a modular C++ pipeline.

For a given number of pulses and a measurement time, the program:

1. Generates simulated meter pulses
2. Delivers them to a **user-space DeviceDriver simulation**
3. Counts the pulses
4. Converts the pulse count into **energy (kWh)**
5. Calculates **average power (W)**
6. Estimates **electricity cost (₹)**
7. Logs the final reading to `logs/meter.log`

> [!IMPORTANT]
> **Clarification on the DeviceDriver.**
> The `DeviceDriver` in this project is a **C++ class running in user space**. It is a *simulation* of a device-driver-like abstraction. It is **not** a Linux kernel module, and no kernel-level code is part of the current implementation.

---

## 2. Problem Statement

Electricity meters report consumption as a stream of pulses. To be useful, those raw pulses must be received, counted, converted into physical units and presented as meaningful information such as energy, power and cost.

This project addresses that problem in a controlled, hardware-free environment. It demonstrates how a **device-facing layer** (the driver abstraction), a **processing layer** (counting and energy conversion), an **analytics layer** (power and cost) and a **persistence layer** (logging) can be separated into independent modules in a Linux/C++ system.

---

## 3. Objectives

- Design and implement a **modular C++17** application for Linux.
- Simulate electricity-meter pulses in software.
- Demonstrate a **device-driver-like abstraction** in user space.
- Convert pulses into energy using the meter constant (1000 pulses = 1 kWh).
- Compute **average power** and **estimated cost** from the measured energy and time.
- Persist readings to a log file using file streams.
- Automate the build with a **Makefile**.
- Document the software architecture with UML and supporting documents.
- Apply the Linux, C++ and system-programming concepts covered during the 20-day training.

---

## 4. Project Type

| Attribute | Details |
|---|---|
| **Category** | Individual Academic Project |
| **Domain** | Linux, Device Drivers, System Programming & C++ |
| **Nature** | Software-based implementation |

---

## 5. Technologies Used

| Technology | Role in the Project |
|---|---|
| **C++** | Primary implementation language |
| **C++17** | Language standard (`-std=c++17`) |
| **g++** | Compiler |
| **Makefile** | Build automation |
| **Linux** | Development and execution environment |
| **Git / GitHub** | Version control and repository hosting |

**Compiler flags used:**


```
g++ -Wall -Wextra -std=c++17 -Iinclude src/main.cpp src/PulseGenerator.cpp src/DeviceDriver.cpp src/PulseCounter.cpp src/EnergyCalculator.cpp src/AnalyticsEngine.cpp src/Logger.cpp -o smart_meter

```

---

## 6. System Architecture

The system follows a **modular layered architecture**. Each module has a single, well-defined responsibility and passes its result to the next stage.

```text
                 SMART ENERGY METER
                         │
                         ▼
                 ┌───────────────┐
                 │Pulse Generator│
                 └───────┬───────┘
                         │
                         ▼
        ┌─────────────────────────────────┐
        │ DeviceDriver (User-space        │
        │ Simulation)                     │
        └────────────────┬────────────────┘
                         │
                         ▼
                 ┌───────────────┐
                 │ Pulse Counter │
                 └───────┬───────┘
                         │
                         ▼
                ┌─────────────────┐
                │Energy Calculator│
                └────────┬────────┘
                         │
                         ▼
                ┌─────────────────┐
                │Analytics Engine │
                └────────┬────────┘
                         │
                         ├── Energy (kWh)
                         └── Power (W)
                         │
                         ▼
                ┌─────────────────┐
                │Cost Calculation │
                └────────┬────────┘
                         │
                         ▼
                    ┌─────────┐
                    │ Logger  │
                    └────┬────┘
                         │
                         ▼
                  logs/meter.log
```

### Layer Summary

| Layer | Module | Responsibility |
|---|---|---|
| Input / Simulation | `PulseGenerator` | Produces simulated meter pulses |
| Device Abstraction | `DeviceDriver` | Receives pulses, holds the pulse count |
| Interface | `PulseCounter` | Retrieves / resets the count from `DeviceDriver` |
| Conversion | `EnergyCalculator` | Pulses → energy (kWh) |
| Analytics | `AnalyticsEngine` | Energy + time → average power (W) |
| Business Calculation | Cost calculation | Energy × tariff → estimated cost |
| Persistence | `Logger` | Writes the reading to `logs/meter.log` |

---

## 7. Data Flow

```text
User Input
    |
    v
Pulse Generation
    |
    v
DeviceDriver Simulation
    |
    v
Pulse Counter
    |
    v
Energy Calculation
    |
    +------------------+
    |                  |
    v                  v
Energy (kWh)     Measurement Time
    |                  |
    +--------+---------+
             |
             v
      Analytics Engine
             |
             v
      Average Power (W)
             |
             v
      Cost Calculation
             |
             v
       Final Reading
             |
             v
          Logger
             |
             v
      logs/meter.log
```

**End-to-end summary:**

```text
Input → Pulse Generation → Device Simulation → Pulse Counting → Energy Calculation → Analytics → Cost Calculation → Logging
```

---

## 8. Device Driver Concept

### 8.1 What the DeviceDriver is in this project

`DeviceDriver` is a **C++ class that simulates the role of a device driver in user space**. In a real system, a driver sits between hardware and the rest of the software and hides hardware details behind a clean interface. `DeviceDriver` reproduces that *software concept*: the rest of the application interacts with the "device" only through its interface.

### 8.2 Responsibilities

| Member | Purpose |
|---|---|
| `handlePulse()` | Receives a simulated pulse and updates the internal state |
| `pulseCount` | Internal state holding the number of pulses received |
| `readPulseCount()` | Returns the current pulse count |
| `reset()` | Resets the pulse count |

### 8.3 How it fits in the system

```text
PulseGenerator ──pulse──▶ DeviceDriver::handlePulse()
                                │
                           pulseCount
                                │
PulseCounter  ◀──read──── DeviceDriver::readPulseCount()
PulseCounter  ───reset──▶ DeviceDriver::reset()
```

`PulseCounter` does not own the count. It acts as an **interface** to the count maintained by `DeviceDriver`.

### 8.4 What this is NOT

> [!WARNING]
> - It is **not** a Linux kernel module.
> - It does **not** register a character device or use kernel APIs.
> - It does **not** communicate with physical hardware.
>
> A real meter or an actual Linux kernel driver is listed only as a **future enhancement** (see [Section 29](#29-future-enhancements)). It is **not** part of the current implementation.

---

## 9. Project Structure

```text
SmartEnergyMeter/
├── src/
│   ├── main.cpp
│   ├── PulseGenerator.cpp
│   ├── DeviceDriver.cpp
│   ├── PulseCounter.cpp
│   ├── EnergyCalculator.cpp
│   ├── AnalyticsEngine.cpp
│   └── Logger.cpp
├── include/
│   ├── PulseGenerator.h
│   ├── DeviceDriver.h
│   ├── PulseCounter.h
│   ├── EnergyCalculator.h
│   ├── AnalyticsEngine.h
│   └── Logger.h
├── docs/
|   ├── STAGE_1_PROJECT_INTRODUCTION.md
│   ├── STAGE_2_PROJECT_REQUIREMENTS_AND_DEVELOPMENT_PLAN.md
│   ├── STAGE_3_SYSTEM_DESIGN_AND_ARCHITECTURE.md
│   ├── STAGE_4_INITIAL_IMPLEMENTATION_AND_PROTOTYPE.md
│   ├── STAGE_5_TESTING_INTEGRATION_AND_IMPROVEMENT.md
│   ├── STAGE_6_FINAL_IMPLEMENTATION_AND_PRESENTATION.md
|   └── PROJECT_REPORT.md
├── logs/
│   └── meter.log
|
├── Makefile
└── README.md
```

| Directory / File | Description |
|---|---|
| `src/` | C++ implementation files |
| `include/` | Header files (class declarations) |
| `tests/` | Directory for test-related material |
| `logs/` | Runtime output; contains `meter.log` |
| `Makefile` | Build automation |
| `README.md` | Project documentation |

---

## 10. Module Description

### 10.1 `PulseGenerator`

Generates simulated electricity-meter pulses.

| Function | Description |
|---|---|
| `generatePulse()` | Generates a single pulse |
| `generateMultiplePulses()` | Generates the requested number of pulses |

### 10.2 `DeviceDriver`

User-space simulation of a device driver. It maintains the pulse count.

| Function | Description |
|---|---|
| `handlePulse()` | Handles an incoming pulse |
| `readPulseCount()` | Returns the current pulse count |
| `reset()` | Resets the pulse count |

### 10.3 `PulseCounter`

Acts as an interface for retrieving and resetting the pulse count from `DeviceDriver`.

| Function | Description |
|---|---|
| `getCount()` | Retrieves the pulse count |
| `reset()` | Resets the pulse count |

### 10.4 `EnergyCalculator`

Converts the pulse count into energy consumption.

```text
Energy (kWh) = Total Pulses / Pulses Per kWh
```

Default meter constant: **1000 pulses/kWh**.

### 10.5 `AnalyticsEngine`

Calculates average power from energy and measurement time.

```text
Power (W) = Energy (kWh) × 3,600,000 / Time (seconds)
```

### 10.6 Cost Calculation

Estimated electricity cost is calculated as:

```text
Cost = Energy Consumed × Electricity Rate
```

Current sample rate: **₹8 per kWh**.

### 10.7 `Logger`

Stores readings in `logs/meter.log`. Logged information includes:

- Pulse count
- Energy consumed
- Average power

### 10.8 `main.cpp`

Entry point. It prompts for input, validates it, coordinates the modules, prints the analytics and triggers logging.

---

## 11. Configuration

| Parameter | Value | Meaning |
|---|---|---|
| Meter constant | `1000 pulses = 1 kWh` | Used by `EnergyCalculator` |
| Electricity tariff | `₹8 per kWh` | Used for cost estimation |
| Log file | `logs/meter.log` | Destination of saved readings |

---

## 12. Requirements

| Requirement | Details |
|---|---|
| Operating System | Linux |
| Compiler | `g++` with C++17 support |
| Build tool | `make` |
| Version control | `git` (for cloning / maintaining the repository) |

No external libraries are required.

---

## 13. Build Instructions

From the project root directory:

```bash
make
```

This compiles the sources in `src/` using the headers in `include/` and produces the executable `smart_meter`.

Compilation uses:

```text
g++ -Wall -Wextra -std=c++17 -Iinclude
```

---

## 14. Run Instructions

```bash
./smart_meter
```

The program prompts for:

```text
Enter number of pulses:
Enter measurement time (hours):
```

**Input validation:** both values must be **positive**.

**Processing steps:**

1. Generate the requested number of pulses
2. Read the total pulses
3. Calculate energy
4. Calculate average power
5. Calculate estimated cost
6. Print the meter analytics
7. Save the reading to `logs/meter.log`

**Display precision:**

| Quantity | Decimal places |
|---|---|
| Energy (kWh) | 3 |
| Other numerical values | 2 |

---

## 15. Example Output

```text
========================================
          SMART ENERGY METER
========================================

Enter number of pulses: 560
Enter measurement time (hours): 5

Simulating meter operation...

----------------------------------------
           METER ANALYTICS
----------------------------------------
Total Pulses       : 560
Energy Consumed    : 0.560 kWh
Measurement Time   : 5.00 hours
Average Power      : 112.00 W
Electricity Rate   : ₹8.00 / kWh
Estimated Cost     : ₹4.48
Reading saved to   : logs/meter.log
System Status      : RUNNING
========================================
```

> [!NOTE]
> The `System Status : RUNNING` line is part of the existing console output. No separate status-management feature is implemented around it.

---

## 16. Example Calculations

### 16.1 Example 1 — 100 pulses, 1 hour

**Energy**

```text
Energy = 100 / 1000 = 0.100 kWh
```

**Average power**

```text
Power = 0.100 × 3,600,000 / 3600
      = 360,000 / 3600
      = 100 W
```

**Estimated cost**

```text
Cost = 0.100 × ₹8 = ₹0.80
```

### 16.2 Example 2 — 250 pulses, 3 hours

**Energy**

```text
Energy = 250 / 1000 = 0.250 kWh
```

**Average power**

```text
Power = 0.250 × 3,600,000 / (3 × 3600)
      = 900,000 / 10,800
      ≈ 83.33 W
```

**Estimated cost**

```text
Cost = 0.250 × ₹8 = ₹2.00
```

### 16.3 Summary

| Pulses | Time (h) | Energy (kWh) | Avg. Power (W) | Cost (₹) |
|---:|---:|---:|---:|---:|
| 100 | 1 | 0.100 | 100.00 | 0.80 |
| 250 | 3 | 0.250 | 83.33 | 2.00 |

---

## 17. Testing and Validation

Testing and validation correspond to **Stage 5** of the training project and are carried out against the behaviour defined in this document:

- **Calculation checks:** program output is compared with the hand-calculated values in [Section 16](#16-example-calculations).
- **Input validation checks:** non-positive values for pulses or measurement time must be rejected.
- **Logging checks:** after a run, `logs/meter.log` should contain the pulse count, energy consumed and average power.
- **Build checks:** the project must compile with `-Wall -Wextra -std=c++17`.

The `tests/` directory is part of the project structure and holds test-related material.

---

## 18. Linux Concepts Used

| Concept | Where it appears |
|---|---|
| Linux development environment | Entire project is developed and run on Linux |
| Linux terminal usage | Build (`make`), execution (`./smart_meter`), interactive input |
| `g++` compilation | Compiling C++17 sources with warning flags |
| Makefile-based build | Build automation (`make`, `make clean`) |
| File system interaction | Writing to `logs/meter.log` |
| Log file handling | Persisting each reading |
| User-space device-driver abstraction | `DeviceDriver` class |
| System programming concepts | Module interaction, I/O, logging, build workflow |

---

## 19. C++ Concepts Used

| Concept | Application in the Project |
|---|---|
| Classes and objects | Each module is a class |
| Encapsulation | State such as `pulseCount` is kept inside the class that owns it |
| Constructors | Initialising module state |
| References | Sharing objects between modules without copying |
| `const` member functions | Read-only operations such as reading the pulse count |
| Header / source separation | `include/*.h` and `src/*.cpp` |
| Include guards | Preventing multiple inclusion of headers |
| C++17 | `-std=c++17` |
| Standard I/O | Console prompts and analytics output |
| File streams | Writing to `logs/meter.log` |
| Error handling | Validation of input values and log-file operations |
| Modular programming | One responsibility per module |
| Static type safety | Strongly typed interfaces checked at compile time |
| Basic object-oriented design | Cooperating objects with clear interfaces |

---

## 20. System Programming Concepts

- **Interaction between software modules** — the output of one module is the input of the next.
- **Device abstraction** — `DeviceDriver` hides pulse handling and state behind a small interface.
- **File I/O** — readings are written to a log file.
- **Logging** — each final reading is persisted in `logs/meter.log`.
- **Command-line interaction** — the program is driven from the Linux terminal.
- **Modular system design** — separate headers and sources per component.
- **Build automation using Makefile** — reproducible compilation and cleanup.
- **Linux development workflow** — edit → build → run → inspect log → commit.

---

## 21. Software Architecture Concepts

Each module follows the **single-responsibility** idea, which gives the project a clear conceptual path:

```text
Linux
  ↓
System Programming
  ↓
Device Driver Concept
  ↓
C++
  ↓
Software Architecture
  ↓
Energy Analytics
  ↓
Logging
```

**Why the modular design helps:**

| Benefit | Explanation |
|---|---|
| **Easier to understand** | Every module can be read and explained on its own |
| **Easier to test** | Modules such as `EnergyCalculator` and `AnalyticsEngine` can be checked independently against known values |
| **Easier to maintain** | A change to one concern (e.g., the tariff or the log format) stays localised |
| **Easier to extend** | A new data source or output can be introduced by replacing or adding a module without rewriting the others |

---

---

## 22. Logging

The `Logger` module writes each reading to:

```text
logs/meter.log
```

**Information logged:**

| Field |
|---|
| Pulse count |
| Energy consumed |
| Average power |

The log uses standard C++ file streams and provides a persistent record of each simulated measurement.

---

## 23. Makefile Commands

| Command | Description |
|---|---|
| `make` | Builds the project and produces the `smart_meter` executable |
| `./smart_meter` | Runs the program |
| `make clean` | Removes build artifacts |

---

## 24. Git and GitHub

The project is maintained with **Git** and intended to be hosted on GitHub.

**Repository name:**

```text
Smart-Energy-Smart-Meter-Pulse-Counter-Analytics-Agent
```

Typical workflow:

```bash
git add .
git commit -m "Describe the change"
git push
```

---

## 25. Project Development Stages

The academic training follows six development stages.

| Stage | Title | Focus |
|:---:|---|---|
| **1** | Project Introduction | Project idea, objective, problem statement, scope, expected outcome |
| **2** | Project Requirements & Development Plan | Scope, modules, features, deliverables, development plan, timeline |
| **3** | System Design & Architecture | Architecture diagrams, major components, data structures, UML diagrams, implementation plan, development environment, Git repository |
| **4** | Initial Implementation & Prototype | Implement core modules, create prototype, integrate components |
| **5** | Testing & Validation | Verify behaviour and calculations |
| **6** | Final Documentation & Presentation | Final documentation and presentation |

---

## 26. Project Scope

### ✅ In Scope (Current Implementation)

- Software-only smart-meter simulation
- Pulse generation
- Pulse counting
- Energy calculation
- Average power calculation
- Electricity cost estimation
- Logging
- Linux / C++ development
- User-space device-driver simulation

### ⛔ Out of Scope (Current Implementation)

- Physical electricity meter
- Arduino
- Raspberry Pi
- Actual IoT hardware
- Cloud backend
- Database
- Web dashboard
- Mobile application
- Machine learning
- Actual Linux kernel module

---

## 27. Limitations

- Pulses are **simulated**; no physical meter is connected.
- `DeviceDriver` is a **user-space simulation**, not a kernel driver.
- The meter constant (1000 pulses/kWh) and tariff (₹8/kWh) are fixed sample values.
- Power is an **average** over the entered measurement time, not a real-time measurement.
- Input is provided interactively; there is no graphical interface.

---

## 28. Future Enhancements

> [!NOTE]
> The items below are **future enhancements only**. None of them is part of the current implementation.

- Real smart-meter hardware integration
- Actual Linux kernel character device driver
- Hardware pulse input
- Real-time monitoring
- Historical analytics
- Graphical dashboard
- Database storage
- Networking
- Advanced energy-consumption analysis

---

## 29. Author

| | |
|---|---|
| **Name** | Aditya Gopal Nayak |
| **Degree** | B.Tech in Computer Science & Engineering |
| **Institute** | Institute of Technical Education and Research (ITER), Siksha 'O' Anusandhan University |
| **Project Type** | Individual Academic Project |

---

## 30. Conclusion

This project brings together the main themes of the training — Linux, C++, device-driver concepts, system programming and software architecture — in one compact application. A simulated pulse stream is received by a user-space `DeviceDriver`, counted, converted into energy, analysed for average power, priced using a fixed tariff and recorded in a log file.

The design keeps every responsibility in its own module, which makes the system easy to explain, verify and extend. The current implementation is intentionally limited to a software simulation; real hardware and a kernel-level driver are identified clearly as future work.
