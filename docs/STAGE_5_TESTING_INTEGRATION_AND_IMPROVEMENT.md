# 🧪 Stage 5 -- Testing, Integration & Improvement

## Smart Energy Smart-Meter Pulse Counter & Analytics Agent

### 1. Stage Objective

Complete testing, integration, debugging, reliability improvement,
code-quality improvement, and documentation updates.

### 2. Testing Strategy

1.  Unit Testing
2.  Integration Testing
3.  System Testing
4.  Input Validation
5.  Logging Verification

### 3. Unit Tests

**U01 -- DeviceDriver Pulse Handling**

``` text
100 simulated pulses → pulseCount = 100
```

**U02 -- DeviceDriver Reset**

``` text
Generate → Read → Reset → Read
Expected final count = 0
```

**U03 -- Energy**

``` text
100 pulses / 1000 = 0.100 kWh
```

**U04 -- Power**

``` text
0.100 kWh / 1 hour = 100.00 W
```

### 4. Integration Tests

**I01 -- Pulse Pipeline**

``` text
PulseGenerator → DeviceDriver → PulseCounter
```

Generated and retrieved counts must match.

**I02 -- Analytics Pipeline**

``` text
Pulses → Energy → Power → Cost
```

**I03 -- Logging** Run the application and verify `logs/meter.log`.

### 5. System Tests

**S01**

``` text
100 pulses, 1 hour
Energy = 0.100 kWh
Power = 100.00 W
Cost = ₹0.80
```

**S02**

``` text
250 pulses, 3 hours
Energy = 0.250 kWh
Power = 83.33 W
Cost = ₹2.00
```

### 6. Negative Tests

**N01:** 0 pulses → reject.

**N02:** Negative pulses → reject.

**N03:** 0 hours → reject.

**N04:** Negative time → reject.

### 7. Validation Checklist

-   [ ] Pulse count matches generated pulses.
-   [ ] DeviceDriver receives pulses.
-   [ ] PulseCounter retrieves correct count.
-   [ ] Energy uses 1000 pulses/kWh.
-   [ ] Power uses measurement duration.
-   [ ] Cost uses ₹8/kWh.
-   [ ] Invalid input is rejected.
-   [ ] Log file receives valid readings.
-   [ ] Makefile builds successfully.
-   [ ] Application runs correctly on Linux.

### 8. Code Quality Improvements

-   Meaningful names
-   Header/source separation
-   Appropriate `const`
-   Input validation
-   No unnecessary globals
-   Compiler warnings
-   Clear formatting
-   Modular responsibilities
-   Updated documentation

### 9. Build Validation

``` bash
make clean
make
./smart_meter
```

### 10. Log Validation

``` bash
cat logs/meter.log
```

Expected format:

``` text
Pulses: 100 | Energy: 0.10 kWh | Average Power: 100.00 W
```

### 11. Issue and Resolution Record

  -----------------------------------------------------------------------
  Issue                   Cause                   Resolution
  ----------------------- ----------------------- -----------------------
  Compilation error       Missing source/header   Correct includes/build
                                                  list

  Invalid input           Non-positive values     Added validation

  Incorrect power         Wrong time conversion   Convert hours to
                                                  seconds

  Log failure             File unavailable        Added stream validation

  Linker error            Missing source          Updated Makefile
  -----------------------------------------------------------------------

Only include issues that actually occurred.

### 12. Stage Deliverables

-   Unit tests
-   Integration tests
-   System tests
-   Negative tests
-   Validation checklist
-   Issue/resolution record
-   Improved implementation
-   Updated documentation
-   Updated Git repository

### 13. Progress Evidence

Terminal outputs, screenshots, test cases, log file, Git history, and
issue/resolution notes.

### 14. Git Commit

``` bash
git add .
git commit -m "test: complete integration and validation"
git push origin main
```

### 15. Demonstration

Show successful build, normal test, larger test, invalid-input test, log
file, and Git history.

### 16. Next Stage

**Stage 6 -- Final Implementation & Presentation**
