# Firmware and Logger Test Checklist — CAN Monitor

Use only an isolated laboratory CAN setup or authorized recorded data. Never connect this prototype to a live vehicle network. The firmware is intended to be receive-only.

## Build and startup

- [ ] Confirm ESP32 board model and pin mapping.
- [ ] Confirm MCP2515 module and oscillator frequency.
- [ ] Confirm CAN bitrate matches the isolated test setup.
- [ ] Install the compatible MCP2515 library.
- [ ] Firmware compiles without errors.
- [ ] Upload completes and startup output appears at 115200 baud.
- [ ] Confirm no CAN controller initialization error.

## Receive and rule checks

- [ ] Receive known frames from an authorized isolated test source.
- [ ] Confirm identifier, DLC and payload formatting.
- [ ] Confirm the example allowlist is documented.
- [ ] Confirm an intentionally unlisted lab-dataset identifier produces the expected alert.
- [ ] Record frame-rate threshold and test conditions.
- [ ] Confirm the prototype does not transmit CAN frames.

## Python logger

- [ ] Install dependencies with `python -m pip install -r requirements.txt`.
- [ ] Identify the correct serial port.
- [ ] Start logger using the documented command.
- [ ] Confirm records are timestamped and saved to CSV.
- [ ] Confirm logger handles serial disconnects or malformed lines as expected.

## Evidence record

| Field | Record |
|---|---|
| Test date | |
| ESP32 and MCP2515 versions | |
| Oscillator and bitrate | |
| Test dataset/source | |
| Number of frames observed | |
| Alerts observed | |
| Logger output file | |
| Firmware commit | |
| Issues and notes | |

Do not claim detection accuracy, false-positive rate or latency without repeatable tests against a documented labeled dataset.
