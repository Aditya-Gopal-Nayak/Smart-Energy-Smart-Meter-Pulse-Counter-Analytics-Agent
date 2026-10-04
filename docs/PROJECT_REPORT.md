# ⚡ SMART ENERGY SMART-METER PULSE COUNTER & ANALYTICS AGENT

## 📘 PROJECT REPORT

**🐧 Linux • 💻 C++17 • 🛠️ System Programming • 🔌 Device Driver Concepts**

| | |
|---|---|
| 🎓 **Project Type** | Individual Academic Project |
| 👤 **Author** | Aditya Gopal Nayak |
| 📚 **Degree** | B.Tech in Computer Science & Engineering |
| 🏛️ **Institute** | Institute of Technical Education and Research (ITER) |
| 🏫 **University** | Siksha 'O' Anusandhan University |

---

## 📑 Table of Contents

| # | Section |
|:-:|---|
| 1️⃣ | [Project Overview & Architecture Specification](#1--project-overview--architecture-specification) |
| 2️⃣ | [Device Driver Interface Contract](#2--device-driver-interface-contract) |
| 3️⃣ | [Pulse Generation and Counting Modules](#3--pulse-generation-and-counting-modules) |
| 4️⃣ | [Energy Calculation and Analytics Engine](#4--energy-calculation-and-analytics-engine) |
| 5️⃣ | [Logging and Build Automation Specification](#5--logging-and-build-automation-specification) |
| 6️⃣ | [Execution Walkthrough, Testing, and Terminal Output](#6--execution-walkthrough-testing-and-terminal-output) |
| 7️⃣ | [Project Structure and Software Concepts](#7--project-structure-and-software-concepts) |
| 8️⃣ | [Development Stages and Final Outcome](#8--development-stages-and-final-outcome) |
| 9️⃣ | [Final Project Summary](#9--final-project-summary) |

---

## 1️⃣ 🧭 Project Overview & Architecture Specification

### 1.1 ❓ Problem Statement

Traditional electricity-meter demonstrations often require physical meter hardware or a dedicated embedded setup to show how meter pulses are converted into useful energy information. For a Linux and C++ system-programming training environment, a software-based model provides a controlled way to demonstrate pulse acquisition, device abstraction, energy calculation, power analytics, cost estimation, and logging.

The project addresses this requirement by simulating smart-meter pulses in a Linux environment. The simulated pulses are passed through a C++ user-space DeviceDriver abstraction, counted, converted into energy consumption, analyzed for average power, and recorded in a log file.

### 1.2 🏗️ Architectural Solution

The Smart Energy Smart-Meter Pulse Counter & Analytics Agent implements a modular software architecture with clear separation of responsibilities:

1. ⚙️ **Pulse Generator** creates the requested number of simulated meter pulses.
2. 🔌 **DeviceDriver** receives the simulated pulses and maintains the pulse count.
3. 🔢 **Pulse Counter** retrieves the count from the DeviceDriver.
4. 🔋 **Energy Calculator** converts pulses into energy in kWh.
5. 📊 **Analytics Engine** calculates average power in Watts using measurement time.
6. 💰 **Cost Calculation** estimates electricity cost using the configured tariff.
7. 📝 **Logger** records the final reading in `logs/meter.log`.

> [!IMPORTANT]
> 🚨 **Important implementation note:** the DeviceDriver is a **user-space C++ simulation**. It is **not** a Linux kernel module and does **not** create a real `/dev` device node.

### 1.3 🗺️ High-Level Architecture

```text
SMART ENERGY METER
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
        |---- Energy (kWh)
        |
        |---- Power (W)
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

### 1.4 🔄 Architectural Workflow and Execution Pipeline

| Stage | | Description |
|:-:|:-:|---|
| **1** | ⌨️ | **User Input** — The application accepts the number of simulated pulses and measurement time in hours. |
| **2** | ⚙️ | **Pulse Generation** — `PulseGenerator` creates the requested number of simulated meter pulses. |
| **3** | 🔌 | **Device Abstraction** — Each pulse is passed to the user-space `DeviceDriver`, which increments its internal pulse count. |
| **4** | 🔢 | **Pulse Retrieval** — `PulseCounter` reads the accumulated count from `DeviceDriver`. |
| **5** | 🔋 | **Energy Calculation** — `EnergyCalculator` converts the pulse count using the meter constant of 1000 pulses/kWh. |
| **6** | 📊 | **Power Analytics** — `AnalyticsEngine` converts energy and elapsed time into average power in Watts. |
| **7** | 💰 | **Cost Calculation** — The application multiplies energy by the configured electricity tariff of ₹8/kWh. |
| **8** | 📝 | **Logging** — `Logger` appends the pulse count, energy, and average power to `logs/meter.log`. |

---

## 2️⃣ 🔌 Device Driver Interface Contract

### 2.1 🎯 Purpose of the DeviceDriver Class

The `DeviceDriver` class establishes the device-abstraction layer between the simulated pulse source and the rest of the application. It stores the current pulse count and provides methods for receiving pulses, reading the count, and resetting the count.

### 2.2 💡 Code Explanation

The class uses a private `unsigned long long` member named `pulseCount`. The constructor initializes this value to zero. `handlePulse()` increments the count whenever `PulseGenerator` produces a pulse. `readPulseCount()` returns the current value as a `const` operation, while `reset()` sets the count back to zero.

### 2.3 📄 Raw Source Code: `include/DeviceDriver.h`

```cpp
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
```

### 2.4 📄 Raw Source Code: `src/DeviceDriver.cpp`

```cpp
#include "DeviceDriver.h"

DeviceDriver::DeviceDriver() {
    pulseCount = 0;
}

void DeviceDriver::handlePulse() {
    pulseCount++;
}

unsigned long long DeviceDriver::readPulseCount() const {
    return pulseCount;
}

void DeviceDriver::reset() {
    pulseCount = 0;
}
```

---

## 3️⃣ ⚙️ Pulse Generation and Counting Modules

### 3.1 ⚡ Pulse Generator

`PulseGenerator` is responsible for producing one or multiple simulated meter pulses. It keeps a reference to `DeviceDriver` and forwards each generated pulse to `handlePulse()`.

### 3.2 📄 Raw Source Code: `include/PulseGenerator.h`

```cpp
#ifndef PULSE_GENERATOR_H
#define PULSE_GENERATOR_H

#include "DeviceDriver.h"

class PulseGenerator {
private:
    DeviceDriver& driver;

public:
    explicit PulseGenerator(DeviceDriver& device);

    void generatePulse();
    void generateMultiplePulses(int numberOfPulses);
};

#endif
```

### 3.3 📄 Raw Source Code: `src/PulseGenerator.cpp`

```cpp
#include "PulseGenerator.h"

PulseGenerator::PulseGenerator(DeviceDriver& device)
    : driver(device) {
}

void PulseGenerator::generatePulse() {
    driver.handlePulse();
}

void PulseGenerator::generateMultiplePulses(int numberOfPulses) {
    if (numberOfPulses <= 0) {
        return;
    }

    for (int i = 0; i < numberOfPulses; i++) {
        generatePulse();
    }
}
```

### 3.4 🔢 Pulse Counter

`PulseCounter` provides a simple interface for retrieving and resetting the count maintained by `DeviceDriver`. It stores a reference to the driver object.

### 3.5 📄 Raw Source Code: `include/PulseCounter.h`

```cpp
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
```

### 3.6 📄 Raw Source Code: `src/PulseCounter.cpp`

```cpp
#include "PulseCounter.h"

PulseCounter::PulseCounter(DeviceDriver& device)
    : driver(device) {
}

unsigned long long PulseCounter::getCount() const {
    return driver.readPulseCount();
}

void PulseCounter::reset() {
    driver.reset();
}
```

---

## 4️⃣ 🔋 Energy Calculation and Analytics Engine

### 4.1 🧮 Energy Calculation

The project uses a meter constant of **1000 pulses per kWh**. `EnergyCalculator` converts the total pulse count into energy consumption.

```text
Energy (kWh) = Total Pulses / Pulses Per kWh
```

Default meter constant:

```text
1000 pulses/kWh
```

### 4.2 📄 Raw Source Code: `include/EnergyCalculator.h`

```cpp
#ifndef ENERGY_CALCULATOR_H
#define ENERGY_CALCULATOR_H

class EnergyCalculator {
private:
    double pulsesPerKWh;

public:
    explicit EnergyCalculator(double pulsesPerKWh = 1000.0);

    double calculateEnergy(unsigned long long pulseCount) const;
};

#endif
```

### 4.3 📄 Raw Source Code: `src/EnergyCalculator.cpp`

```cpp
#include "EnergyCalculator.h"

EnergyCalculator::EnergyCalculator(double pulsesPerKWh)
    : pulsesPerKWh(pulsesPerKWh) {
}

double EnergyCalculator::calculateEnergy(
    unsigned long long pulseCount) const {

    if (pulsesPerKWh <= 0) {
        return 0.0;
    }

    return static_cast<double>(pulseCount) / pulsesPerKWh;
}
```

### 4.4 📊 Analytics Engine

`AnalyticsEngine` calculates average electrical power from energy consumption and elapsed time. The result is returned in Watts.

```text
Power (W) = Energy (kWh) × 3,600,000 / Time (seconds)
```

### 4.5 📄 Raw Source Code: `include/AnalyticsEngine.h`

```cpp
#ifndef ANALYTICS_ENGINE_H
#define ANALYTICS_ENGINE_H

class AnalyticsEngine {
public:
    AnalyticsEngine();

    double calculateAveragePower(
        double energyKWh,
        double elapsedSeconds) const;
};

#endif
```

### 4.6 📄 Raw Source Code: `src/AnalyticsEngine.cpp`

```cpp
#include "AnalyticsEngine.h"

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
```

### 4.7 💰 Cost Calculation

The current application uses a sample electricity tariff of **₹8 per kWh**. The estimated cost is calculated as:

```text
Cost = Energy Consumed × Electricity Rate
```

Example:

```text
0.100 kWh × ₹8/kWh = ₹0.80
```

---

## 5️⃣ 📝 Logging and Build Automation Specification

### 5.1 🎯 Purpose of the Logger

The `Logger` module provides persistent file-based recording of meter readings. It appends pulse count, energy, and average power to `logs/meter.log`.

### 5.2 📄 Raw Source Code: `include/Logger.h`

```cpp
#ifndef LOGGER_H
#define LOGGER_H

#include <string>

using namespace std;

class Logger {
public:
    explicit Logger(const std::string& filename);

    void logReading(
        unsigned long long pulses,
        double energyKWh,
        double averagePower);

private:
    string filename;
};

#endif
```

### 5.3 📄 Raw Source Code: `src/Logger.cpp`

```cpp
#include "Logger.h"

#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

Logger::Logger(const std::string& filename)
    : filename(filename) {
}

void Logger::logReading(
    unsigned long long pulses,
    double energyKWh,
    double averagePower) {

    ofstream logFile(filename, ios::app);

    if (!logFile) {
        cerr << "Error: Unable to open log file.\n";
        return;
    }

    logFile << fixed << setprecision(2);

    logFile << "Pulses: " << pulses
            << " | Energy: " << energyKWh << " kWh"
            << " | Average Power: " << averagePower << " W"
            << '\n';

    logFile.close();
}
```

### 5.4 🛠️ Makefile Specification

The Makefile coordinates compilation of the C++ source files using `g++`. It uses C++17, enables common compiler warnings, and adds the include directory to the compiler search path.

### 5.5 📄 Raw Source Code: `Makefile`

```makefile
CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

TARGET = smart_meter

SRC = src/main.cpp \
      src/PulseGenerator.cpp \
      src/DeviceDriver.cpp \
      src/PulseCounter.cpp \
      src/EnergyCalculator.cpp \
      src/AnalyticsEngine.cpp \
      src/Logger.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
```

---

## 6️⃣ 🧪 Execution Walkthrough, Testing, and Terminal Output

### 6.1 🚀 Prerequisites and Compilation Commands

The application is designed for a Linux development environment with a C++17 compiler and Make.

```bash
sudo apt update

sudo apt install -y build-essential g++ make

make

./smart_meter
```

To remove the compiled executable:

```bash
make clean
```

### 6.2 🖥️ Current Main Program Behavior

The program accepts two positive values from the user: the number of simulated pulses and the measurement time in hours. It then performs the complete meter-processing pipeline.

```text
Enter number of pulses: 100

Enter measurement time (hours): 1

Simulating meter operation...
```

### 6.3 📄 Raw Source Code: `src/main.cpp`

```cpp
#include <iostream>
#include <iomanip>

#include "DeviceDriver.h"
#include "PulseCounter.h"
#include "PulseGenerator.h"
#include "EnergyCalculator.h"
#include "AnalyticsEngine.h"
#include "Logger.h"

using namespace std;

int main() {

    DeviceDriver driver;

    PulseCounter counter(driver);
    PulseGenerator generator(driver);
    EnergyCalculator energyCalculator;
    AnalyticsEngine analytics;
    Logger logger("logs/meter.log");

    int simulatedPulses;
    double measurementTimeHours;

    // Meter configuration
    const double electricityRate = 8.0; // ₹8 per kWh

    cout << "========================================\n";
    cout << "          SMART ENERGY METER\n";
    cout << "========================================\n";

    cout << "\nEnter number of pulses: ";
    cin >> simulatedPulses;

    cout << "Enter measurement time (hours): ";
    cin >> measurementTimeHours;

    // Validate input
    if (simulatedPulses <= 0 || measurementTimeHours <= 0) {
        cout << "\nError: Please enter valid positive values.\n";
        return 1;
    }

    cout << "\nSimulating meter operation...\n";

    generator.generateMultiplePulses(simulatedPulses);

    unsigned long long totalPulses = counter.getCount();

    double energy =
        energyCalculator.calculateEnergy(totalPulses);

    double elapsedSeconds =
        measurementTimeHours * 3600.0;

    double averagePower =
        analytics.calculateAveragePower(
            energy,
            elapsedSeconds
        );

    double estimatedCost =
        energy * electricityRate;

    cout << "\n";
    cout << "----------------------------------------\n";
    cout << "           METER ANALYTICS\n";
    cout << "----------------------------------------\n";

    cout << "Total Pulses       : "
         << totalPulses << endl;

    cout << fixed << setprecision(3);

    cout << "Energy Consumed    : "
         << energy << " kWh" << endl;

    cout << fixed << setprecision(2);

    cout << "Measurement Time   : "
         << measurementTimeHours << " hours" << endl;

    cout << "Average Power      : "
         << averagePower << " W" << endl;

    cout << "Electricity Rate   : ₹"
         << electricityRate << " / kWh" << endl;

    cout << "Estimated Cost     : ₹"
         << estimatedCost << endl;


    logger.logReading(
        totalPulses,
        energy,
        averagePower
    );

    cout << "Reading saved to   : logs/meter.log\n";
    cout << "System Status      : RUNNING\n";

    cout << "========================================\n";

    return 0;
}
```

### 6.4 📟 Demonstration Output

```text
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

### 6.5 ✅ Test Case 1: Baseline Meter Reading

**📥 Input**

- 🔹 Number of pulses: `100`
- 🔹 Measurement time: `1 hour`

**🧮 Expected calculation**

```text
Energy = 100 / 1000
       = 0.100 kWh

Power  = (0.100 × 3,600,000) / 3600
       = 100 W

Cost   = 0.100 × 8
       = 0.80 ₹
```

> ✔️ The test verifies the complete normal execution path from pulse generation through logging.

### 6.6 ✅ Test Case 2: Larger Pulse Count

**📥 Input**

- 🔹 Number of pulses: `250`
- 🔹 Measurement time: `3 hours`

**🧮 Expected result**

```text
Energy        = 250 / 1000
              = 0.250 kWh

Average Power = 83.33 W

Estimated Cost = 2.00 ₹
```

### 6.7 ⛔ Test Case 3: Invalid Input

The program validates that both the pulse count and measurement time are positive.

```text
Enter number of pulses: 0

Enter measurement time (hours): 1

Error: Please enter valid positive values.
```

> ⚠️ The program terminates with an error return value when invalid non-positive input is supplied.

### 6.8 🗂️ Logging Verification

After a successful execution, the reading is appended to:

```text
logs/meter.log
```

The stored information includes:

- 🔢 Pulse count
- 🔋 Energy consumed in kWh
- ⚡ Average power in Watts

---

## 7️⃣ 🧱 Project Structure and Software Concepts

### 7.1 📁 Project Directory Structure

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
|   └── PROJECT_REPORT.md
├── logs/
│   └── meter.log
├── Makefile
└── README.md
```

### 7.2 🐧 Linux Concepts Demonstrated

- 🖥️ Linux terminal-based development
- 🔨 `g++` compilation
- 🛠️ Makefile-based build automation
- 🗃️ File-system interaction
- 📝 File-based logging
- 🔌 User-space device-driver abstraction
- 🔁 Linux system-programming workflow

### 7.3 💻 C++ Concepts Demonstrated

- 🧩 Classes and objects
- 🔒 Encapsulation
- 🏗️ Constructors
- 🔗 References
- 🛡️ `const` member functions
- 📂 Header/source separation
- 🚧 Include guards
- 🆕 C++17
- ⌨️ Standard input/output
- 📄 File streams
- ✅ Input validation
- 🧱 Modular programming
- 🎯 Basic object-oriented design

### 7.4 🏛️ Software Architecture Concepts

The project applies **separation of responsibilities** by assigning pulse generation, device abstraction, pulse counting, energy calculation, analytics, cost estimation, and logging to separate modules. This makes the application easier to understand, test, maintain, and extend.

### 7.5 📐 UML Documentation

The project documentation includes a `docs/uml/` directory intended for UML representations such as:

- 🧬 Class Diagram
- 🔀 Sequence Diagram
- 🔄 State Machine Diagram

These diagrams document the relationships and execution flow of the software architecture.

---

## 8️⃣ 🏁 Development Stages and Final Outcome

| Development Stage | | Outcome |
|---|:-:|---|
| **Stage 1 – Project Introduction** | 💡 | Defined the project idea, objective, problem statement, scope, and expected outcome. |
| **Stage 2 – Project Requirements & Development Plan** | 📋 | Defined requirements, modules, features, deliverables, and development plan. |
| **Stage 3 – System Design & Architecture** | 🏗️ | Prepared the architecture, data flow, module structure, and UML documentation plan. |
| **Stage 4 – Initial Implementation & Prototype** | 💻 | Implemented the core C++ modules and integrated them into a working prototype. |
| **Stage 5 – Testing & Validation** | 🧪 | Tested module behavior, calculations, input validation, integration, and logging. |
| **Stage 6 – Final Documentation & Presentation** | 📘 | Prepared project documentation, README, final report, GitHub submission, and presentation material. |

### 8.1 🎯 Final Outcome

The completed prototype demonstrates a full software pipeline for simulated smart-meter processing. It accepts user input, generates and counts pulses, calculates energy and average power, estimates cost, displays the results, and stores the reading in a log file.

### 8.2 📌 Scope and Limitations

**✅ Current scope**

- ✔️ Software-only smart-meter simulation
- ✔️ Pulse generation and counting
- ✔️ Energy calculation
- ✔️ Average-power analytics
- ✔️ Electricity cost estimation
- ✔️ File-based logging
- ✔️ Linux and C++17 development
- ✔️ User-space DeviceDriver simulation

**⚠️ Current limitations**

- ❌ No physical electricity meter is connected.
- ❌ The DeviceDriver is not a Linux kernel module.
- ❌ Pulse input is simulated in software.
- ❌ No database, cloud service, web dashboard, or mobile application is implemented.

### 8.3 🔭 Future Enhancements

> [!NOTE]
> 🔮 The items below are **future enhancements only** and are not part of the current implementation.

- 🔌 Integration with a real smart-meter hardware interface
- 🐧 Replacement of the user-space abstraction with an actual Linux kernel character driver if required
- 📡 Real hardware pulse acquisition
- ⏱️ Real-time monitoring
- 📈 Historical energy analytics
- 🖼️ Graphical dashboard
- 🗄️ Database-backed storage
- 🌐 Network-based meter data transmission

---

## 9️⃣ 🏆 Final Project Summary

The **Smart Energy Smart-Meter Pulse Counter & Analytics Agent** successfully combines Linux, C++17, system programming, device-driver concepts, modular architecture, energy calculation, analytics, and file handling into one academic software project.

The project demonstrates the complete path from simulated meter pulses to useful electrical measurements. With a meter constant of **1000 pulses/kWh** and a sample tariff of **₹8/kWh**, the application converts pulse data into energy, power, and cost information and records the results.

The implementation is intentionally software-based. The DeviceDriver abstraction demonstrates the device-driver concept in user space without claiming kernel-level implementation. This keeps the current project aligned with the implemented C++ source while leaving a clear path for future hardware or kernel-driver integration.

---

