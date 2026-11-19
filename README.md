# CAN Bus Intrusion Detection System

A defensive embedded/PC monitoring prototype intended to observe CAN frames on an isolated laboratory network, flag traffic that differs from configured expectations, and display events for analysis.

## Objectives
- Receive CAN frames using an ESP32 and MCP2515 module.
- Record identifiers, data length, payload, and timestamps where available.
- Forward frame information to a PC over USB serial.
- Compare traffic with a configured identifier allowlist and message-rate baseline.
- Log and display events in a Python dashboard.
- Evaluate behavior using repeatable, labeled laboratory data.

## Hardware and software
ESP32 development board, MCP2515 CAN module, isolated CAN test nodes, USB cable, PC, Python 3, and optionally Streamlit for the dashboard.

## Architecture
Isolated CAN test network → MCP2515 → ESP32 → USB serial → Python receiver → rule checks/logging → dashboard.

## Detection approach
- Identifier allowlist: flag identifiers outside the configured test set.
- Message-rate threshold: flag identifiers exceeding a documented baseline rate.

These simple checks can produce false positives and miss other abnormal behavior. Alerts indicate rule mismatches; they do not prove malicious activity.

## Repository
- docs/system_design.md — architecture and configuration record.
- docs/safe_testing.md — defensive test cases and metrics.

## Hardware verification
MCP2515 modules vary. Confirm oscillator frequency, supply and logic levels, bitrate, termination, and pin connections from the exact module documentation. ESP32 GPIO pins are not 5 V tolerant.

## Validation status
No detection percentage or latency result is claimed here. Publish metrics only with a repeatable test method and raw evidence.

## Safety
Use only a disconnected, isolated CAN bench or synthetic data. Never inject experimental frames into a vehicle in operation. Do not use this project to disrupt, manipulate, or evade vehicle communications.

## Author
Gurubaran G K — B.E. Electronics and Communication Engineering.
