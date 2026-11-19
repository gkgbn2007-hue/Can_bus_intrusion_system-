# Software and Library Requirements — CAN Monitor

## Firmware

- Arduino IDE or a compatible ESP32 development environment
- ESP32 board package
- MCP2515 Arduino library compatible with the `MCP2515.h` API (the starter sketch uses the autowp/arduino-mcp2515 style API)
- SPI library supplied with the Arduino core

Select the exact ESP32 board model and port before compiling. Confirm the MCP2515 module oscillator setting (8 MHz or 16 MHz) and set the sketch accordingly.

## Python serial logger

Python 3.9 or later is recommended.

Install dependency:

```bash
python -m pip install pyserial
```

Run on Windows:

```bash
python can_serial_logger.py --port COM5
```

Run on Linux (example port):

```bash
python can_serial_logger.py --port /dev/ttyUSB0
```

Replace the example port with the serial port shown by your operating system.

## Serial format

Firmware emits records such as:

- `CAN,<hex_id>,<dlc>,<hex_payload>`
- `ALERT,UNLISTED_ID,<hex_id>`
- `ALERT,HIGH_FRAME_RATE,<count>`

The Python tool timestamps and stores received records in a CSV file. It is a logger, not a CAN transmitter or a validated intrusion-classification system.
