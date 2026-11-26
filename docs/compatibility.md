# Using Serial across targets

The only project dependency is the matching `serial-contract`. Keep its API revision aligned with this Core.

Application code can exchange portable 16-bit frame values without making assumptions about the native register width. Review supported parity and stop symbols, line rate tolerance and what constitutes a corrupt frame on the replacement target.

This repository's host simulations and shared API compile/link checks provide source-level evidence. Target timing and physical behavior require hardware validation.
