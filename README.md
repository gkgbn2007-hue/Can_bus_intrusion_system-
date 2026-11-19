# CAN Bus Intrusion Detection System

A defensive embedded monitoring prototype for observing CAN traffic on an isolated laboratory network, flagging selected rule mismatches, and recording events on a computer.

## Project overview

The project demonstrates a basic receive-only CAN monitoring pipeline using an ESP32, MCP2515 CAN controller and a Python serial logger.

### Main features

- Receive CAN frames through an MCP2515 module.
- Display received identifier, data length and payload over USB serial.
- Compare received standard identifiers against a configurable example allowlist.
- Demonstrate a simple frame-count threshold alert.
- Capture serial records and timestamps in a CSV file using Python.
- Keep the firmware receive-only; no CAN frame transmission is implemented.

## Hardware and software

| Component | Purpose |
|---|---|
| ESP32 development board | Main controller |
| MCP2515 CAN module | CAN frame reception |
| Isolated CAN training network | Controlled test traffic |
| USB cable | Firmware upload and serial output |
| Computer with Python 3 | Serial logging and analysis |

Confirm the actual MCP2515 oscillator, logic levels, bitrate and termination requirements for your module.

## System architecture

```mermaid
flowchart LR
    LAB["Isolated CAN test network"] --> MCP["MCP2515"]
    MCP --> ESP["ESP32 receive-only monitor"]
    ESP --> RULES["Example allowlist and rate checks"]
    RULES --> USB["USB Serial"]
    USB --> PY["Python logger"]
    PY --> CSV["CSV event log"]
```

See [system architecture](docs/system_architecture.md).

## Repository structure

- `firmware/esp32_can_receive_monitor.ino` — receive-only ESP32 firmware.
- `tools/can_serial_logger.py` — Python serial-to-CSV logger.
- `docs/system_architecture.md` — architecture and data flow.
- `docs/pin_connections.md` — proposed ESP32/MCP2515 pin mapping.
- `docs/libraries.md` — firmware and Python setup.
- `docs/testing_procedure.md` — isolated bench test procedure.
- `docs/system_design.md` — initial design notes.
- `docs/safe_testing.md` — defensive testing and safety notes.

## Firmware setup

1. Install the ESP32 board package in Arduino IDE.
2. Install a compatible MCP2515 library exposing the `MCP2515.h` API.
3. Open `firmware/esp32_can_receive_monitor.ino`.
4. Confirm the ESP32 pin mapping, MCP2515 oscillator and CAN bitrate.
5. Compile and upload to the ESP32.
6. Open Serial Monitor at **115200 baud**.

The example sketch assumes an 8 MHz MCP2515 oscillator and 500 kbit/s CAN bitrate. These values must match the actual module and isolated test network.

## Python logger setup

Install Python dependency:

```bash
python -m pip install pyserial
```

Run on Windows:

```bash
python tools/can_serial_logger.py --port COM5
```

Run on Linux (replace the example port as needed):

```bash
python tools/can_serial_logger.py --port /dev/ttyUSB0
```

The logger creates or appends to `can_monitor_log.csv`.

## Detection logic

- **Identifier allowlist:** reports identifiers outside the configured example list.
- **Frame-count threshold:** reports when the total number of received frames in a one-second window exceeds the demonstration threshold.

These are simple demonstration rules. They can produce false positives and false negatives and do not establish that a message is malicious.

## Validation status and limitations

The code is a starter implementation and has not been represented as hardware-tested. No detection accuracy, latency, or false-positive rate is claimed. Such metrics require a documented, labeled dataset, repeatable test conditions and retained logs.

The current firmware uses standard 11-bit identifier handling for its example logic. Extend and validate the design before claiming support for additional CAN frame types or advanced detection.

## Safety

Use only an isolated laboratory CAN setup or recorded/synthetic data. Do not connect this educational prototype to a live vehicle network. The firmware is receive-only and must not be used to disrupt, manipulate, or evade vehicle communications.

## Author

**Gurubaran G K**  
B.E. Electronics and Communication Engineering
