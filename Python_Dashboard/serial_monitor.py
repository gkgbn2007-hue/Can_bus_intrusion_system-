"""Passive CAN serial monitor for an isolated laboratory setup.

An unexpected identifier is a review flag, not proof of an attack.
"""
import argparse
import csv
from datetime import datetime, timezone
from pathlib import Path

import serial

HEADER = ["timestamp_utc", "can_id", "extended", "dlc", "data_hex", "status"]


def parse_record(line):
    parts = line.strip().split(",")
    if len(parts) != 5 or parts[0] != "FRAME":
        return None
    _, can_id, extended, dlc, data_hex = parts
    can_id_int = int(can_id, 16)
    dlc_int = int(dlc)
    if not 0 <= dlc_int <= 8 or len(data_hex) != dlc_int * 2:
        raise ValueError("Invalid DLC or payload length")
    bytes.fromhex(data_hex)
    return can_id_int, int(extended), dlc_int, data_hex.upper()


def main():
    parser = argparse.ArgumentParser(description="Passive CAN serial monitor")
    parser.add_argument("--port", required=True, help="Serial port, e.g. COM5 or /dev/ttyUSB0")
    parser.add_argument("--baud", type=int, default=115200)
    parser.add_argument("--allow", default="", help="Comma-separated hexadecimal IDs for this lab scenario")
    parser.add_argument("--log", default="can_frames.csv")
    args = parser.parse_args()

    allowed = None
    if args.allow.strip():
        allowed = {int(item.strip(), 16) for item in args.allow.split(",") if item.strip()}

    log_path = Path(args.log)
    new_file = not log_path.exists()

    with log_path.open("a", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)
        if new_file:
            writer.writerow(HEADER)

        with serial.Serial(args.port, args.baud, timeout=1) as ser:
            print(f"Listening on {args.port} at {args.baud} baud. Ctrl+C to stop.")
            while True:
                raw = ser.readline().decode("utf-8", errors="replace").strip()
                if not raw:
                    continue
                if raw.startswith("STATUS,"):
                    print(raw)
                    continue
                try:
                    record = parse_record(raw)
                    if record is None:
                        continue
                    can_id, extended, dlc, data_hex = record
                    status = "OBSERVED"
                    if allowed is not None and can_id not in allowed:
                        status = "REVIEW_UNKNOWN_ID"
                    timestamp = datetime.now(timezone.utc).isoformat()
                    writer.writerow([timestamp, f"{can_id:X}", extended, dlc, data_hex, status])
                    f.flush()
                    print(f"{timestamp} ID={can_id:X} DLC={dlc} DATA={data_hex} {status}")
                except (ValueError, csv.Error) as exc:
                    print(f"Rejected serial record: {exc}")


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\nMonitor stopped.")
