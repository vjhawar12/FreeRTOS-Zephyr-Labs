# STM32 RTOS Drivers with FreeRTOS

A hands-on embedded firmware lab series focused on **FreeRTOS**, **register-level STM32 drivers**, and **hardware/software integration** on microcontrollers.

This repository builds from core RTOS primitives into practical embedded applications: task scheduling, deterministic timing, queues, semaphores, mutexes, interrupt-to-task signaling, peripheral driver integration, and system diagnostics.

## Highlights

- Register-level STM32F401RE peripheral configuration using CMSIS
- FreeRTOS task scheduling, queues, semaphores, mutexes, timers, and task notifications
- Custom SPI2 driver and ADXL345 accelerometer driver
- RTOS-based sensor acquisition and processing pipeline
- Planned I2C distance/proximity sensor integration
- Modular driver/application separation for reusable embedded firmware

---

## Low-Level Driver Work

This repo includes a register-level SPI2 driver for the STM32F401RE and an ADXL345 accelerometer driver layered on top of it.

- `common/drivers/spi.c` — SPI2 initialization, GPIO alternate-function setup, chip-select control, and blocking SPI transfers
- `common/drivers/adxl345.c` — ADXL345 register access, device ID check, measurement configuration, and multi-byte XYZ sample reads

This demonstrates direct peripheral configuration, reusable bus-driver design, and device-driver integration under FreeRTOS.

---

## Lab Progression

### RTOS Foundations

| Lab | Topic | Concepts |
|---|---|---|
| Lab 1 | Multiple Tasks and Priorities | task creation, scheduling, priorities, stack sizing |
| Lab 2 | Periodic Tasks | `vTaskDelayUntil()`, deterministic timing, periodic execution |
| Lab 3 | Queues | producer/consumer design, inter-task data transfer |
| Lab 4 | Binary Semaphores | event signaling, blocked task behavior |
| Lab 5 | Mutexes | shared resource protection, priority inversion awareness |
| Lab 6 | Task Notifications | lightweight task signaling |
| Lab 7 | Software Timers | one-shot timers, periodic timers, deferred actions |
| Lab 8 | Interrupts with RTOS | `FromISR` APIs, ISR-to-task signaling |
| Lab 9 | UART CLI | command parsing, runtime debug interface |

### Hardware Integration and System Design

| Lab | Topic | Concepts |
|---|---|---|
| Lab 10 | SPI Accelerometer Integration | ADXL345 driver, acquisition task, queue-based processing |
| Lab 11 | I2C Distance Sensor Integration | I2C bus driver, proximity/range sensor driver, periodic sampling |
| Lab 12 | Multi-Sensor RTOS Application | SPI + I2C telemetry, mixed-rate tasks, modular architecture |
| Lab 13 | System Health and Reliability | stack/heap monitoring, watchdog concepts, fault handling |

---

## Current Focus

The current hardware integration path is centered on building a small drone/robotics-style telemetry node:

```text
SPI accelerometer task      ┐
                            ├── sensor queue → processing/logging task → UART output
I2C distance sensor task    ┘
