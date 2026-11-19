# System Architecture

Isolated CAN test nodes
  -> MCP2515 module
  -> ESP32
  -> USB serial
  -> Python serial monitor
  -> CSV log and review flags

## Data flow
1. MCP2515 receives frames from the isolated CAN test network.
2. ESP32 reads each received frame and prints a structured serial record.
3. Python validates the record and writes a timestamped CSV row.
4. If an optional lab allowlist is supplied, identifiers outside it are marked for review.

## Limitations
- This starter is a passive monitor, not a complete intrusion-detection product.
- Identifier allowlisting alone cannot establish malicious intent.
- The source has not been compiled or tested against the user's exact module and library version.
- Confirm oscillator, logic levels, bitrate, wiring, and library API before hardware use.
