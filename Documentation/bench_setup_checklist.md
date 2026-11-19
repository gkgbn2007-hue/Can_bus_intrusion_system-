# Isolated CAN Bench Setup Checklist

Use a disconnected laboratory CAN network or synthetic data only. Do not connect this project to a live vehicle network.

## Verify before connecting
- [ ] Exact ESP32 development-board model identified.
- [ ] Exact MCP2515 module and oscillator frequency identified.
- [ ] Module supply voltage and logic-level requirements checked.
- [ ] ESP32 GPIO pins are protected from any 5 V signal.
- [ ] SPI and interrupt pin mapping verified for the actual board.
- [ ] CAN bitrate matches the isolated test network.
- [ ] Correct CAN termination is present at the two physical ends of the test bus.
- [ ] CAN_H and CAN_L wiring checked against module documentation.
- [ ] Test network is electrically isolated from any vehicle.

## Software setup
1. Install Arduino IDE and a compatible MCP_CAN library.
2. Check the installed library's begin() signature and oscillator constants; versions may differ.
3. Select the correct ESP32 board and serial port.
4. Upload ESP32_Firmware/can_monitor.ino.
5. Install Python dependencies with: python -m pip install -r Python_Dashboard/requirements.txt
6. Run: python Python_Dashboard/serial_monitor.py --port COM5
7. Replace COM5 with the serial port shown on your computer.

## Data interpretation
The optional allowlist labels identifiers outside the configured set as REVIEW_UNKNOWN_ID. This is a review flag only, not proof of malicious activity. Establish a known-good lab baseline before drawing conclusions.
