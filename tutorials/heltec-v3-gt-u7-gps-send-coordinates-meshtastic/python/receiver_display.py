# Connects to the Meshtastic serial interface, subscribes to incoming messages, and formats GPS/position fields for display and logging.
#
# Full tutorial: https://shillehtek.com/blogs/news/heltec-v3-gt-u7-gps-send-coordinates-meshtastic
# Parts used: https://shillehtek.com/products/gt-u7-gps-module-presoldered-1
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
#             https://shillehtek.com/products/shillehtek-400-point-breadboard
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import sys
import time
from datetime import datetime
from pathlib import Path
from typing import Any

import meshtastic.serial_interface
from pubsub import pub


def pick_first(mapping: dict[str, Any], *keys: str) -> Any:
    for key in keys:
        if key in mapping and mapping[key] not in (None, ""):
            return mapping[key]
    return None


def format_value(value: Any, digits: int = 6) -> str:
    if value is None:
        return "-"
    if isinstance(value, float):
        return f"{value:.{digits}f}"
    return str(value)


def format_timestamp(epoch: Any) -> str:
    if not epoch:
        return datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    try:
        return datetime.fromtimestamp(float(epoch)).strftime("%Y-%m-%d %H:%M:%S")
    except (TypeError, ValueError, OSError):
        return datetime.now().strftime("%Y-%m-%d %H:%M:%S")


def normalize_coordinate(value: Any) -> Any:
    if value is None:
        return None
    try:
        numeric = float(value)
    except (TypeError, ValueError):
        return value
    if abs(numeric) > 180:
        return numeric * 1e-7
    return numeric


class PositionPrinter:
    def __init__(self, sender_id: str | None = None, csv_path: Path | None = None) -> None:
        self.sender_id = sender_id.lower() if sender_id else None
        self.csv_path = csv_path
        if self.csv_path:
            self.csv_path.parent.mkdir(parents=True, exist_ok=True)
            file_exists = self.csv_path.exists()
            self.csv_file = self.csv_path.open("a", newline="", encoding="utf-8")
            self.csv_writer = csv.writer(self.csv_file)
            if not file_exists:
                self.csv_writer.writerow(
                    [
                        "received_at",
                        "from_id",
                        "node_name",
                        "latitude",
                        "longitude",
                        "altitude_m",
                        "sats_in_view",
                        "speed_m_s",
                    ]
                )
                self.csv_file.flush()
        else:
            self.csv_file = None
            self.csv_writer = None

    def close(self) -> None:
        if self.csv_file:
            self.csv_file.close()

    def _node_name(self, packet: dict[str, Any], interface: Any) -> str:
        from_num = packet.get("from")
        node = interface.nodesByNum.get(from_num, {}) if from_num is not None else {}
        user = node.get("user", {})
        return (
            pick_first(user, "longName", "shortName")
            or packet.get("fromId")
            or f"node-{from_num}"
        )

    def _should_print(self, packet: dict[str, Any]) -> bool:
        if not self.sender_id:
            return True
        from_id = str(packet.get("fromId", "")).lower()
        return from_id == self.sender_id

    def on_position(self, packet: dict[str, Any], interface: Any) -> None:
        if not self._should_print(packet):
            return

        decoded = packet.get("decoded", {})
        position = decoded.get("position", {}).copy()
        from_num = packet.get("from")
        if from_num is not None:
            cached_position = interface.nodesByNum.get(from_num, {}).get("position", {})
            if isinstance(cached_position, dict):
                position = {**cached_position, **position}

        latitude = normalize_coordinate(pick_first(position, "latitude", "latitudeI"))
        longitude = normalize_coordinate(pick_first(position, "longitude", "longitudeI"))
        altitude = pick_first(position, "altitude", "altitudeMsl")
        sats = pick_first(position, "satsInView", "sats_in_view")
        speed = pick_first(position, "groundSpeed", "ground_speed")
        timestamp = pick_first(position, "timestamp", "time", "lastHeard")

        node_name = self._node_name(packet, interface)
        if packet.get("fromId"):
            from_id = packet["fromId"]
        elif from_num is not None:
            from_id = f"!{from_num:x}"
        else:
            from_id = "unknown"
        when = format_timestamp(timestamp)

        print(
            f"[{when}] {node_name} ({from_id}) "
            f"lat={format_value(latitude)} lon={format_value(longitude)} "
            f"alt={format_value(altitude, 1)}m sats={format_value(sats, 0)} "
            f"speed={format_value(speed, 2)}m/s"
        )
        sys.stdout.flush()

        if self.csv_writer:
            self.csv_writer.writerow(
                [
                    when,
                    from_id,
                    node_name,
                    latitude,
                    longitude,
                    altitude,
                    sats,
                    speed,
                ]
            )
            self.csv_file.flush()


def on_connection(interface: Any, topic: Any = pub.AUTO_TOPIC) -> None:
    local_info = interface.localNode
    local_user = local_info.get("user", {}) if isinstance(local_info, dict) else {}
    local_name = pick_first(local_user, "longName", "shortName") or "unknown"
    print(f"Connected to receiver node: {local_name}")
    print("Waiting for Meshtastic GPS position packets...")
    sys.stdout.flush()


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Listen for Meshtastic position packets and print coordinates."
    )
    parser.add_argument(
        "--port",
        help="Receiver node serial port, for example /dev/cu.usbserial-0001",
    )
    parser.add_argument(
        "--sender-id",
        help="Optional sender node ID to filter, for example !abcd1234",
    )
    parser.add_argument(
        "--csv",
        type=Path,
        help="Optional CSV log path, for example positions.csv",
    )
    return parser


def main() -> int:
    args = build_parser().parse_args()
    printer = PositionPrinter(sender_id=args.sender_id, csv_path=args.csv)

    pub.subscribe(on_connection, "meshtastic.connection.established")
    pub.subscribe(printer.on_position, "meshtastic.receive.position")

    interface = None
    try:
        if args.port:
            interface = meshtastic.serial_interface.SerialInterface(devPath=args.port)
        else:
            interface = meshtastic.serial_interface.SerialInterface()

        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("\nStopping listener.")
        return 0
    finally:
        printer.close()
        if interface is not None:
            interface.close()


if __name__ == "__main__":
    raise SystemExit(main())
