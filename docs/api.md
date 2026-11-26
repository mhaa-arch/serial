# Use the Serial Core

Public entry headers are [serial/serial.hpp](../include/serial/serial.hpp).

## Configure the format first

Construct `Serial` from a live `Peripheral&`. `configure` rejects a zero bit rate, a width outside 1–16 and an asynchronous frame with no stop symbols. Other acceptance decisions belong to the Adapter. Check the result before sending or reading.

After `try_write` accepts a frame, check `transmission_complete` if later work depends on the wire being idle. While polling `try_read`, keep the previous value on busy or an error. Use caller-managed scheduling for retries and handle frame or overrun errors according to the application protocol.

## Composition and lifetime

Application code calls the Serial Core. It borrows the matching Contract, which an Adapter implements using its Hardware Definitions. Future Devices will create or bind these objects and establish their lifetime. To use the examples today, construct the facade directly with the supplied fake. Keep each borrowed resource alive for its use by the facade and follow the Adapter's access and synchronization requirements.
