# PumpResp 3.3 V‑logic notes  
The PumpResp design can operate with 3.3 V‑logic Nano‑family boards (Nano 33 BLE, Nano 33 IoT, RP2040, Nano ESP32), which may provide additional functionality.

This topic is outside the scope of the main build guide. Several design and assembly adjustments are required, and the list below reflects unverified considerations only—not tested, not validated, and not intended as full instructions.

1. Replace the 5 V relay module with a relay module that is both 3.3 V‑logic compatible and powered from a 3–3.3 V supply.

2. If any connected device communicates over 5 V I²C, use a bidirectional logic‑level converter. This protects the 3.3 V Arduino pins and ensures reliable two‑way I²C communication.

3. All remaining PumpResp components (status LED, push button, PWM control signals) operate correctly at 3.3 V logic levels.

4. If PumpResp is connected over UART to the PyroScience FireSting logger, 3.3 V logic is actually preferable and aligns with the logger’s voltage levels.