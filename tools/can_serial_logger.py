"""
CAN monitor serial logger
Receives CSV-like records from the ESP32 defensive CAN monitor.
Install: python -m pip install pyserial
Run:     python can_serial_logger.py --port COM5
Linux:   python can_serial_logger.py --port /dev/ttyUSB0

Use only with an isolated laboratory CAN setup or recorded test data.
This script logs observations; it does not transmit CAN frames.
"""

import argparse
import csv
from datetime import datetime, timezone
from pathlib import Path

import serial


def main():
    parser = argparse.ArgumentParser(description="Log ESP32 CAN monitor output")
    parser.add_argument("--port", required=True, help="Serial port, e.g. COM5")
    parser.add_argument("--baud", type=int, default=115200)
    parser.add_argument("--output", default="can_monitor_log.csv")
    args = parser.parse_args()

    output_path = Path(args.output)
    new_file = not output_path.exists()

    with serial.Serial(args.port, args.baud, timeout=1) as ser, \
            output_path.open("a", newline="", encoding="utf-8") as file:
        writer = csv.writer(file)
        if new_file:
            writer.writerow(["timestamp_utc", "record_type", "field_1",
                             "field_2", "field_3"])

        print(f"Listening on {args.port} at {args.baud} baud. Ctrl+C to stop.")
        try:
            while True:
                raw = ser.readline().decode("utf-8", errors="replace").strip()
                if not raw:
                    continue

                print(raw)
                parts = raw.split(",", 3)
                timestamp = datetime.now(timezone.utc).isoformat()

                if parts[0] == "CAN":
                    writer.writerow([timestamp, "CAN",
                                     parts[1] if len(parts) > 1 else "",
                                     parts[2] if len(parts) > 2 else "",
                                     parts[3] if len(parts) > 3 else ""])
                elif parts[0] == "ALERT":
                    writer.writerow([timestamp, "ALERT",
                                     parts[1] if len(parts) > 1 else "",
                                     parts[2] if len(parts) > 2 else "",
                                     ""])
                else:
                    writer.writerow([timestamp, "INFO", raw, "", ""])
                file.flush()
        except KeyboardInterrupt:
            print("\nStopped. Log saved to", output_path)


if __name__ == "__main__":
    main()
