# Isolated Bench Testing Procedure

> Test only on a dedicated, isolated CAN training setup or recorded test data. Do not connect this prototype to a live vehicle network. The supplied firmware is receive-only.

## 1. Pre-checks

- Identify the ESP32 board and MCP2515 module.
- Confirm the module oscillator (8 MHz or 16 MHz).
- Confirm the lab CAN bitrate and compatible transceivers.
- Check CANH/CANL polarity and bus termination.
- Keep the test network disconnected from any vehicle.

## 2. Firmware startup

- Install the required ESP32 board package and MCP2515 library.
- Set the oscillator constant to match the module.
- Compile and upload the sketch.
- Open Serial Monitor at 115200 baud.
- Confirm the startup message appears without a CAN setup error.

## 3. Receive/log check

- Use a known-good isolated CAN training source that is already configured for the same bitrate.
- Confirm received frames are printed with identifier, DLC and payload.
- Run the Python logger on the correct serial port.
- Confirm records are saved to the output CSV.

## 4. Alert logic check

- Review the example allowlist in the sketch and replace it with identifiers from your authorized lab dataset.
- Confirm a received identifier outside that list is reported as an unlisted-ID alert.
- Confirm the rate alert threshold is treated as a simple demonstration threshold, not a calibrated security boundary.

## 5. Test record

| Test | Expected observation | Actual result |
|---|---|---|
| ESP32 startup | Firmware ready message | To be recorded |
| CAN controller setup | No initialization error | To be recorded |
| Frame reception | Frame appears on serial output | To be recorded |
| Python logger | CSV file is created and appended | To be recorded |
| Unlisted identifier | Alert appears for test dataset entry | To be recorded |
| High frame count | Demonstration threshold alert | To be recorded |

Record the board versions, bitrate, oscillator, dataset source and logs. Do not claim detection accuracy or false-positive rates without a repeatable labeled dataset and measured results.
