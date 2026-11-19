# Pin Connections — ESP32 CAN Monitor

> This is an assumed wiring reference for the starter sketch. Confirm your ESP32 board, MCP2515 module, oscillator frequency and logic-voltage compatibility before connecting.

## Example ESP32 VSPI mapping

| MCP2515 module | Classic ESP32 pin | Purpose |
|---|---:|---|
| SCK | GPIO18 | SPI clock |
| SO (MISO) | GPIO19 | SPI data to ESP32 |
| SI (MOSI) | GPIO23 | SPI data from ESP32 |
| CS | GPIO5 | Chip select |
| INT | GPIO4 | Interrupt output |
| GND | GND | Common ground |
| VCC | Per module specification | Verify supply and logic levels |

## CAN bus connection

Connect CANH to CANH and CANL to CANL on the isolated bench CAN network. Use proper bus termination at the two physical ends of the bus as required by the transceiver/network design. Do not add extra termination blindly.

## Configuration assumptions

The starter sketch currently assumes:

- MCP2515 oscillator: 8 MHz (`MCP_8MHZ`)
- CAN bitrate: 500 kbit/s
- Standard 11-bit identifiers in its example allowlist
- ESP32 serial output: 115200 baud

Change these only to match the actual hardware and documented lab setup.

## Safety boundary

Use this receiver-only monitor on an isolated laboratory network or recorded data. Do not connect it to a live vehicle network, and do not transmit frames or attempt to disrupt vehicle communication.
