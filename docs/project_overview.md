# Project Documentation — CAN Bus Intrusion Detection System

## 1. Abstract

This project is a defensive CAN bus monitoring prototype intended for an isolated laboratory network. An MCP2515 CAN controller receives frames and passes them to an ESP32. The ESP32 reports frame identifiers, data length and payload information over USB serial. A Python utility records the received information and alert messages in a CSV file.

The starter logic demonstrates an example identifier allowlist and a simple frame-count threshold. These rules are educational examples and are not a validated automotive intrusion detection system.

## 2. Problem Statement

CAN is used as an in-vehicle communication network. Learning how to observe and analyze CAN traffic is important for embedded and automotive engineering. A controlled monitoring prototype can help demonstrate frame reception, logging and simple rule-based anomaly indicators without transmitting messages.

## 3. Objectives

- Receive CAN frames using an MCP2515 module.
- Use an ESP32 to process and report received frame information.
- Demonstrate an example identifier allowlist check.
- Demonstrate a simple message-rate threshold.
- Send observations to a computer over serial.
- Store records in CSV format for offline analysis.

## 4. Existing System

Manual observation of CAN traffic can be difficult to organize and review. Without a structured log, comparing frame identifiers and event timing across a test session may be inconvenient.

## 5. Proposed System

The proposed educational setup uses an isolated CAN training network, MCP2515 module, ESP32 and a Python serial logger. The firmware receives frames and reports them. The host computer stores the records for later review.

## 6. Hardware Requirements

| Component | Role |
|---|---|
| ESP32 development board | Main controller |
| MCP2515 CAN module | CAN controller/interface |
| Isolated CAN training nodes | Controlled source of test traffic |
| USB cable | Programming and serial connection |
| Computer | Python logging and analysis |

Confirm oscillator frequency, transceiver arrangement, supply voltage, logic compatibility and termination for the exact module.

## 7. Software Requirements

- Arduino IDE or compatible ESP32 toolchain
- ESP32 board package
- MCP2515 library compatible with the sketch API
- Python 3
- pyserial Python package
- CSV-compatible spreadsheet or analysis tool

## 8. Working Principle

1. A controlled isolated CAN training setup provides known test traffic.
2. MCP2515 receives CAN frames.
3. ESP32 reads the received frame information.
4. The firmware reports frame identifiers, data length and payload bytes over serial.
5. Example rules can flag identifiers outside a configured allowlist or a frame count above a demonstration threshold.
6. The Python logger records observations and timestamps in a CSV file.

## 9. Applications

- Embedded and automotive communication education.
- CAN frame reception and serial logging demonstrations.
- Offline analysis of authorized laboratory datasets.
- Learning basic rule-based monitoring concepts.

## 10. Advantages

- Demonstrates an end-to-end embedded-to-PC monitoring pipeline.
- Provides structured logs for later review.
- Uses simple rules that are easy to explain.
- Starter firmware is receive-only.

## 11. Limitations

- The allowlist and frame-rate checks are basic examples.
- Rules can produce false positives and false negatives.
- No detection accuracy or latency result is claimed.
- No advanced classification or validated automotive security function is included.
- Hardware configuration depends on the exact MCP2515 module and lab network.

## 12. Future Enhancements

- Build a labeled and repeatable isolated CAN dataset.
- Add per-identifier baseline analysis using measured normal traffic.
- Improve event visualization and filtering in the host application.
- Evaluate false-positive rate, detection rate and processing delay using documented tests.
- Add unit tests for parsing and logging.
- Keep all experimentation confined to isolated laboratory equipment and recorded data.

## 13. Testing and Validation

Follow [the isolated bench testing procedure](testing_procedure.md). Record board versions, oscillator frequency, bitrate, dataset source, test conditions and raw logs. Do not claim detection performance without measured evidence.

## 14. Conclusion

The project demonstrates a receive-only CAN monitoring and logging workflow using an ESP32, MCP2515 and Python. It provides a foundation for learning CAN frame observation and simple defensive monitoring in a controlled environment.

## 15. References

- Espressif ESP32 documentation: https://docs.espressif.com/projects/esp-idf/en/stable/esp32/
- Microchip MCP2515 product information: https://www.microchip.com/en-us/product/MCP2515
- Python documentation: https://docs.python.org/3/
- pySerial documentation: https://pyserial.readthedocs.io/
