/*
  CAN Bus Defensive Monitor — ESP32 + MCP2515
  For isolated laboratory CAN benches or synthetic test networks ONLY.
  Passively receives frames and prints them over USB serial.
  Verify module, oscillator, voltage levels, bitrate, termination, and pins.
*/
#include <SPI.h>
#include <mcp_can.h>

static const int CAN_CS_PIN = 5;   // Common ESP32 example; verify your board.
static const int CAN_INT_PIN = 4;  // Common ESP32 example; verify your board.
static const long SERIAL_BAUD = 115200;

// Verify whether the actual MCP2515 module uses an 8 MHz or 16 MHz crystal.
static const byte MCP2515_CLOCK = MCP_8MHZ;
static const byte CAN_BITRATE = CAN_500KBPS; // Must match isolated lab bus.

MCP_CAN CAN0(CAN_CS_PIN);

void setup() {
  Serial.begin(SERIAL_BAUD);
  pinMode(CAN_INT_PIN, INPUT);

  // MCP_CAN library APIs differ by version; check your installed library.
  while (CAN0.begin(MCP2515_CLOCK, CAN_BITRATE, MCP_8MHZ) != CAN_OK) {
    Serial.println("STATUS,ERROR,CAN_INIT_FAILED");
    delay(1000);
  }

  CAN0.setMode(MCP_NORMAL);
  Serial.println("STATUS,OK,CAN_MONITOR_READY");
  Serial.println("FRAME,ID,EXTENDED,DLC,DATA_HEX");
}

void loop() {
  if (digitalRead(CAN_INT_PIN) == LOW) {
    unsigned long canId = 0;
    byte len = 0;
    byte data[8] = {0};

    if (CAN0.readMsgBuf(&canId, &len, data) == CAN_OK) {
      const bool extended = (canId & 0x80000000UL) != 0;
      canId &= 0x1FFFFFFFUL;

      Serial.print("FRAME,");
      Serial.print(canId, HEX);
      Serial.print(",");
      Serial.print(extended ? 1 : 0);
      Serial.print(",");
      Serial.print(len);
      Serial.print(",");

      for (byte i = 0; i < len && i < 8; i++) {
        if (data[i] < 0x10) Serial.print("0");
        Serial.print(data[i], HEX);
      }
      Serial.println();
    }
  }
}
