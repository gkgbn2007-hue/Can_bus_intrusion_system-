# Defensive Test Cases — CAN Bus Intrusion Monitoring

> Status: planned verification cases. No live-vehicle testing is intended or authorized.

| ID | Test | Procedure | Expected observation | Result |
|---|---|---|---|---|
| CAN-01 | Controller startup | Start the ESP32 and CAN controller on an isolated bench setup | Initialization status is reported | Not run |
| CAN-02 | Normal frame reception | Use a dedicated, isolated CAN test fixture with benign sample frames | Frames are received and logged with identifier and length | Not run |
| CAN-03 | Allowlist classification | Replay approved, benign identifiers from a controlled test fixture | Known identifiers are classified as allowed | Not run |
| CAN-04 | Unknown identifier classification | Use a controlled fixture to present a harmless, pre-recorded unknown identifier | Monitor marks it for review according to configured policy | Not run |
| CAN-05 | Rate baseline | Replay a fixed, benign test trace at a documented rate | Measured rate and threshold behavior are logged | Not run |
| CAN-06 | Python logger | Feed a captured serial log file or mock serial input to the logger | Output is parsed and saved without crashing | Not run |

## Safety boundary
- Use only a disconnected, isolated lab CAN network or offline recorded data.
- Do not connect this prototype to a road-going vehicle or safety-critical vehicle network.
- Do not transmit, inject, flood, or manipulate CAN traffic. This project is for passive defensive monitoring.
- Verify transceiver voltage levels, termination, and board compatibility before bench use.

## Evidence to add after testing
Record fixture details, CAN bitrate, benign trace source, firmware version, test date, expected/observed classification, and sanitized logs. Change a result to **Pass** or **Fail** only after the test is actually performed.
