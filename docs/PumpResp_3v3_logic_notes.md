# PumpResp 3.3 V‑logic notes  
PumpResp can operate with 3.3 V‑logic Nano‑family boards (Nano 33 BLE, Nano 33 IoT, RP2040, Nano ESP32), which may provide additional functionality.

This topic is outside the scope of the main build guide. Several design and assembly adjustments are required, and the list below reflects unverified considerations only.

1. Replace the 5 V relay module with a relay module that is both 3.3 V‑logic compatible and powered from a 3–3.3 V supply.

2. The remaining PumpResp components (status LED, push button) operate correctly at 3.3 V logic level.
3.3 V I²C pins of the Arduino board (SDA and SCL)

3. If any connected device communicates over 5 V I²C, use a bidirectional logic‑level converter on the I²C lines (SDA and SCL). This protects the 3.3 V I²C pins of the Arduino board (SDA and SCL).

4. If PumpResp is connected over UART to the PyroScience FireSting logger, 3.3 V logic is actually preferable and aligns with the logger’s voltage levels.