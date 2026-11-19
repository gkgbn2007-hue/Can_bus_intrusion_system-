/*
 * Defensive CAN Bus Monitor - starter firmware
 * Target: ESP32 + MCP2515 CAN controller, isolated bench network only.
 *
 * Example wiring for a classic ESP32 using VSPI:
 * SCK=18, MISO=19, MOSI=23, CS=5, INT=4.
 * Verify your exact ESP32 board and MCP2515 module before use.
 *
 * Library: autowp/arduino-mcp2515 (mcp2515.h)
 * Set MCP_8MHZ or MCP_16MHZ to match the module oscillator.
 * Set CAN bitrate to match the isolated lab network.
 *
 * This sketch ONLY receives and reports frames. It does not transmit.
 * The allowlist example below applies to standard 11-bit identifiers.
 */

#include <SPI.h>
#include <mcp2515.h>

static const uint8_t CAN_CS_PIN = 5;
static const uint8_t CAN_INT_PIN = 4;
static const uint32_t SERIAL_BAUD = 115200;
static const uint32_t RATE_WINDOW_MS = 1000;
static const uint16_t MAX_FRAMES_PER_WINDOW = 100;

static const uint16_t ALLOWED_STANDARD_IDS[] = {0x100, 0x101, 0x200};
static const size_t ALLOWED_COUNT =
    sizeof(ALLOWED_STANDARD_IDS) / sizeof(ALLOWED_STANDARD_IDS[0]);

MCP2515 canController(CAN_CS_PIN);
struct can_frame rxFrame;

uint32_t windowStartMs = 0;
uint16_t framesInWindow = 0;

bool isAllowedStandardId(uint16_t id) {
  for (size_t i = 0; i < ALLOWED_COUNT; i++) {
    if (ALLOWED_STANDARD_IDS[i] == id) return true;
  }
  return false;
}

void printFrame(const struct can_frame &frame) {
  const bool isExtended = (frame.can_id & CAN_EFF_FLAG) != 0;
  const uint32_t id = isExtended
      ? (frame.can_id & CAN_EFF_MASK)
      : (frame.can_id & CAN_SFF_MASK);

  Serial.print(F("CAN,"));
  if (isExtended) Serial.print(F("EXT:"));
  Serial.print(id, HEX);
  Serial.print(',');
  Serial.print(frame.can_dlc);
  Serial.print(',');

  const uint8_t dataLength = frame.can_dlc > 8 ? 8 : frame.can_dlc;
  for (uint8_t i = 0; i < dataLength; i++) {
    if (frame.data[i] < 0x10) Serial.print('0');
    Serial.print(frame.data[i], HEX);
  }
  Serial.println();
}

void setup() {
  Serial.begin(SERIAL_BAUD);
  pinMode(CAN_INT_PIN, INPUT_PULLUP);
  SPI.begin(18, 19, 23, CAN_CS_PIN);

  canController.reset();

  // Change MCP_8MHZ to MCP_16MHZ if required by your module.
  if (canController.setBitrate(CAN_500KBPS, MCP_8MHZ) != MCP2515::ERROR_OK) {
    Serial.println(F("ERROR: CAN bitrate setup failed."));
    while (true) delay(500);
  }

  if (canController.setNormalMode() != MCP2515::ERROR_OK) {
    Serial.println(F("ERROR: CAN normal mode setup failed."));
    while (true) delay(500);
  }

  windowStartMs = millis();
  Serial.println(F("CAN monitor ready; receive-only lab prototype."));
  Serial.println(F("Format: CAN,<hex_id_or_EXT:hex_id>,<dlc>,<hex_payload>"));
}

void loop() {
  const uint32_t now = millis();

  if (digitalRead(CAN_INT_PIN) == LOW) {
    if (canController.readMessage(&rxFrame) == MCP2515::ERROR_OK) {
      framesInWindow++;

      const bool isExtended = (rxFrame.can_id & CAN_EFF_FLAG) != 0;
      if (isExtended) {
        // Do not truncate an extended 29-bit ID and compare it as an
        // unrelated standard 11-bit identifier.
        Serial.print(F("ALERT,EXTENDED_ID_NOT_IN_STANDARD_ALLOWLIST,"));
        Serial.println(rxFrame.can_id & CAN_EFF_MASK, HEX);
      } else {
        const uint16_t standardId = rxFrame.can_id & CAN_SFF_MASK;
        if (!isAllowedStandardId(standardId)) {
          Serial.print(F("ALERT,UNLISTED_ID,"));
          Serial.println(standardId, HEX);
        }
      }

      printFrame(rxFrame);
    }
  }

  if (now - windowStartMs >= RATE_WINDOW_MS) {
    if (framesInWindow > MAX_FRAMES_PER_WINDOW) {
      Serial.print(F("ALERT,HIGH_FRAME_RATE,"));
      Serial.println(framesInWindow);
    }
    framesInWindow = 0;
    windowStartMs = now;
  }
}
