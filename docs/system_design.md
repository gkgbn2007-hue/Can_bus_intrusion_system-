# System Design — CAN Bus Intrusion Detection System

## Intended architecture
Isolated CAN test nodes → MCP2515 module → ESP32 → USB serial → Python receiver → rule checks → event log/dashboard.

## Functional blocks
1. CAN reception: MCP2515 receives frames from the isolated test network.
2. Embedded monitoring: ESP32 reads received frame information and forwards structured serial records.
3. PC receiver: Python reads and validates the serial records.
4. Rule checks: compare identifiers with a scenario-specific allowlist and message rates with a documented baseline.
5. Logging/dashboard: record frames and alerts for later review.

## Configuration to record
- ESP32 board model and board package version.
- MCP2515 module model, oscillator frequency, supply and logic levels.
- Verified SPI and interrupt pin mapping.
- CAN bitrate and termination arrangement.
- Serial baud rate and record format.
- Python and package versions.
- Test scenario, allowed identifiers, and baseline rates.

An alert means a configured rule was not met. It does not establish intent or prove an intrusion. Use only a disconnected, isolated CAN bench or synthetic data.
