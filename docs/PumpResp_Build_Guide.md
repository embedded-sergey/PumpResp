---
title: "PumpResp Build Guide"
author: "Sergey Morozov"
date: "11 May 2026"
revision: "0.4"
toc: true
toc-depth: 3
---

# PumpResp Build Guide
**Revision:** 0.4  
**Author:** Sergey Morozov  
**Date:** 12 May 2026

<!-- begin-md-image -->
![PumpResp Device](images/pumpresp_photo.jpg)
<!-- end-md-image -->


# Table of Contents

1. [Introduction](#1-introduction)
2. [Safety Notes](#2-safety-notes)  
   2.1 [Environmental Safety](#21-environmental-safety)  
   2.2 [Electrical Safety](#22-electrical-safety)  
   2.3 [Mechanical and Tool Safety](#23-mechanical-and-tool-safety)
3. [Bill of Materials](#3-bill-of-materials)
4. [Tools and Consumables](#4-tools-and-consumables)
5. [Assembly Instructions](#5-assembly-instructions)  
   5.1 [Preparing the enclosure](#51-preparing-the-enclosure)  
   5.2 [Installing power distribution components](#52-installing-power-distribution-components)  
   5.3 [Installing the control-side electronics](#53-installing-the-control-side-electronics)  
   5.4 [Adding the user interface components](#54-adding-the-user-interface-components)  
   5.5 [Enabling communication with other devices (optional)](#55-enabling-communication-with-other-devices-optional)  
   5.6 [Finalizing the enclosure](#56-finalizing-the-enclosure)
6. [Software Setup](#6-software-setup)   
   6.1 [Installing the Arduino IDE and uploading firmware](#61-installing-the-arduino-ide-and-uploading-firmware)   
   6.2 [Configuring the data‑logging software](#62-configuring-the-data‑logging-software)   
   6.3 [Establishing the serial connection and recording data](#63-establishing-the-serial-connection-and-recording-data)    
   6.4 [Exporting and managing recorded data](#65-exporting-and-managing-recorded-data)
7. [Functional Testing and Verification](#7-functional-testing-and-verification)
8. [Appendices](#8-appendices)

---

# 1. Introduction

PumpResp is an open‑source device for controlling pumps and recording pump‑phase data used in intermittent‑flow respirometry. It can operate up to eight 5–24 V DC pumps and transmit data to a computer over USB. The device can also communicate with external dissolved‑oxygen meters to enable threshold‑based pump activation in addition to simple time‑based control.

This guide explains how to assemble the hardware step by step. It covers preparing the enclosure, wiring the electronics, installing the user‑interface components, and loading the software. The document focuses strictly on construction and verification; experimental applications and biological context are described separately in the accompanying manuscript.

**User skill level.** The build guide is intended for students, technicians, and researchers with basic technical skills. No engineering background is required. Users should be comfortable with simple soldering and basic multimeter measurements (continuity and DC voltage).

**Assembly environment.** PumpResp can be assembled in any standard workspace equipped for basic electronics and mechanical tasks, including university or biological‑station workshops, applied‑sciences laboratories, or local FabLabs (a global directory is provided by the Fab Foundation). The enclosure can be purchased and modified or fabricated using a 3D printer.

**Estimated build time.** Assembly, software setup, and full functional verification typically require 2–4 days for a first‑time build depending on user skills. When assembling multiple identical units, the per‑device time decreases substantially as enclosure preparation and wiring become more routine.

## Versioning

This guide corresponds to PumpResp hardware, software, and documentation release **v1.0.0**.

Source files and updates are available in the public repository:  
<https://github.com/embedded-sergey/PumpResp>

## Licensing

- **Software:** GPL‑3.0  
- **Hardware designs:** CERN-OHL-S v2 
- **Documentation (including this guide):** CC‑BY‑4.0  

These licenses ensure open access, modifiability, and reproducibility across all components of the PumpResp platform.

# 2. Safety Notes

## 2.1 Environmental Safety

PumpResp is designed to be water-resistant, providing protection against accidental splashes and operation in high humidity environments. To reduce moisture accumulation in humid environment, place an absorbent pack inside the enclosure. PumpResp is not waterproof: if the device is submerged or dropped into the water, immediately power it off, disconnect the USB cable  and do not resume operation until the enclosure and internal components have been thoroughly inspected and dried.

## 2.2 Electrical Safety

PumpResp operates at 5-24 VDC, which falls within the extra-low-voltage category recognized in electrical safety standards worldwide. Devices operating at ≤ 24 VDC are generally considered safe for personal, educational, and research use, and in most countries can be built and used without electrical certification, provided that a certified external power supply is used and no mains‑voltage wiring is modified. 

The power supply unit must include integrated overcurrent protection (fuse or electronic limit) and should be selected based on the total power requirements of the connected pumps. For example, if eight pumps each draw 0.3 A at 12 V, the total current is 2.4 A. In this case, a 12 V, 4 A power supply provides sufficient overhead for safe operation (i.e., operating below ~70% of the power supply unit's maximum rated output). The minimum recommended wire size for regular 5-12V is 24 AWG and 20 AWG for high‑current pump circuits.

During assembly and testing, follow basic electrical‑safety practices. Keep the device disconnected from any power source while you work. Check the polarity of every wire before connecting power, and avoid any contact between the positive and negative lines. Before turning the device on, inspect all solder joints, connectors, and insulation to make sure nothing is loose or exposed. Use a multimeter to check your wiring: confirm that each connection has continuity and make sure there are no accidental shorts. Switch the device on only when you’re sure all connections are correct.

## 2.3 Mechanical and Tool Safety

Use adhesive materials, mechanical and electrical tools listed in the section "Tools and Consumables” with care. If you are inexperienced with some of them, seek assistance from a trained technician. Wear personal protection equipment: protective glasses and fume mask, especially when soldering and use heat‑resistant mat to protect your workspace. During the assembly process run the tests referred in the assembly instructions to make the assembly process to be safe and verify the quality of PumpResp.

# 3. Bill of Materials

Price estimates for generic components use Amazon.com  as a reference, based on pricing available in March 2026. Amazon is chosen because it provides broad international availability, relatively stable pricing, and consistent product listings, which makes it a practical baseline for reproducible cost estimates. Because many components on Amazon are sold only in bulk packs, the bill of materials lists the price of the entire pack even when only one piece is needed, which inflates the apparent cost of a single device and results in unnecessary surplus. In practice, individual components can often be purchased at lower cost from suppliers that support small‑quantity or single‑unit purchasing, including local electronics stores, online marketplaces, and global engineering distributors such as Mouser or Digi‑Key. Prices for specialized sensors and measurement devices are taken directly from manufacturers’ websites when these items are not consistently available through the above distributors.

| Part Name | Manufacturer | Quantity | Unit Price (USD)¹ | Total Price (USD) | Notes |
|-----------|--------------|----------|--------------------|--------------------|-------|
| Industrial ABS enclosure, IP65, 200×120×75 mm | Generic | 1 pc | 10 | 10 | – |
| 2‑pin waterproof automotive connectors | Generic | 1 set (10 male–female pairs) | 9 | 9 | Female connectors are also needed for pumps connected to PumpResp |
| PWM motor speed controller, 1.8–12 V, 2 A | Generic | 8 pcs | 2 | 16 | 6–28 V PWM controllers can be used instead, but not with 5 V pumps |
| Red and black wires, 20 AWG | Generic | 3 m each | 7 | 7 | Use 16 AWG for high‑current pumps |
| 2-pin round rocker switch | Generic | 1 pc | 5 | 5 | Bulk pack (3–5 pcs) |
| DC socket power jack, steel, 5.5×2.1 mm | Generic | 1 pc | 7 | 7 | Bulk pack (3–5 pcs) |
| 1-channel relay, 5 V logic, 30 V, 10 A | Generic | 1 pc | 10 | 10 | Bulk pack (5–10 pcs). It can be replaced by 3.3 V logic relay if 3.3 V-logic Nano board is used² |
| Arduino Nano–compatible board (ATmega328P) with Mini-B USB cable and screw‑terminal adapter | Generic | 1 kit | 9 | 9 | The board can be replaced by the Arduino Nano rev.3 or 3.3 V-board from Nano family² |
| M6 machine screw, 6 mm | Generic | 1 pc | 5 | 5 | Bulk pack (60–300 pcs) |
| Push button, 25×19 mm | Generic | 1 pc | 7 | 7 | Bulk pack (5–10 pcs) |
| LED, 5 mm | Generic | 1 pc | 5 | 5 | Bulk pack (50–200 pcs) |
| Resistor, 220 Ω, ¼ W | Generic | 1 pc | 5 | 5 | Bulk pack (20–200 pcs) |
| Female to male jumper wires, square jumpers, 10 cm | Generic | 1 kit | 4 | 4 | – |

**Grand total: 99 USD**

*¹ Unit prices reflect the smallest purchasable quantity on Amazon.com. When only bulk packs are available, the listed price corresponds to the full pack even if a single piece is required.*

*² The design is compatible with 3.3 V‑logic Arduino Nano–family boards (e.g., Nano Every, Nano 33 IoT, Nano 33 BLE) provided that the 5 V relay module is replaced with a 3 V/3.3 V logic‑compatible relay module powered from 3–3.3 V. All other digital I/O (status LED, push button, PWM control signals) operate correctly at 3.3 V logic levels.*


# 4. Tools and Consumables
These items are not included in the BOM because they are general workshop supplies rather than project‑specific components, but they are still required for assembly. Most of the tools and consumables can be found in FabLabs, electronic/robotics clubs and Universities of Applied Sciences around the world.

Mechanical tools:
* utility cutter
* long-nose pliers
* wire cutters
* screwdriver 
* drill with step drill bit
* rotary tool with 1 mm drill bit

Electrical tools and materials:
* soldering iron
* solder wire
* flux
* heat-shrink tubing
* electrical tape

Adhesives:
* hot-glue gun
* hot-glue sticks
* superglue

Measuring and marking tools:
* multimeter
* ruler
* pencil

Safety tools:
* protective glasses
* fume mask
* heat-resistant mat

# 5. Assembly Instructions
This section contains 36 assembly steps covering mechanical preparation, wiring, and installation of all power‑distribution and control components. Before beginning the assembly, note that several steps in Sections 5 and 6 have corresponding functional checks in Section 7. These checks can be performed immediately after completing each relevant assembly step or after the full assembly is finished. Performing the checks in parallel with assembly helps identify wiring mistakes early and reduces the risk of component damage.

## 5.1 Preparing the enclosure
PumpResp can be assembled using either a commercially available enclosure or the provided 3D‑printed enclosure. For the printed version, drilling (Steps 2–5) is not required; the STL files are available in the PumpResp repository.

**Step 1.** Unscrew the cover to open the enclosure.

**Step 2.** Mark out the hole positions on the base and on the cover of the enclosure using a ruler and a pencil, as shown in Figure 1.

Figure 1. Blueprint of the PumpResp enclosure: 
TODO: - add the top recess 
      - increase power whole
      - add (optional) to UART connection

**Step 3.** If you use components with different form factors, or if you use an enclosure with different dimensions, adjust the blueprint accordingly or mark out the positions on the fly.

**Step 4.** Drill the holes in the marked layout on the enclosure, then adjust the hole geometry using a utility cutter.

**Step 5.** For oval‑shaped holes on the rear panel, drill two overlapping holes and shape the opening with a cutter or a rotary tool, including the top recess.

**Step 6.** Remove the two protrusions on the bottom side of each body of a male waterproof connector using a utility cutter or a rotary tool with a sanding disk.

**Step 7.** Assemble eight male waterproof connectors with 8 cm wires. Ensure that the red wire is inserted into port 1 of the connector and the black wire into port 2, respectively. Incorrect color order can lead to wiring errors.

**Step 8.** Insert the waterproof connectors into the oval‑shaped holes and secure them to the enclosure wall using a hot‑glue gun.

## 5.2 Installing power distribution components
**Step 9.** Mount the PWM controllers to the front panel of the enclosure.

**Step 10.** Connect the male waterproof connector wires to the Power (+) and Power (–) terminals of the corresponding PWM controller located in front of the connector (see [Check 1](#check-1-wiring-continuity-of-amp-plugs-and-pwm-modules)).

Figure 2. Wiring scheme of the PumpResp: 
TODO: ---

**Step 11.** Assemble the two red and two black multi‑wire junctions by soldering the wire bundles as shown in Figure 3. Insulate all exposed solder joints with electrical tape to ensure no bare wires remain.

Figure 3. Assembly wires and multi‑wire junctions: 
TODO: ---

**Step 12.** Connect the red wires to the Motor (+) and the black wires to the Motor (–) terminals of each PWM controller as illustrated in Figure 2.

**Step 13.** Mount the rocker power switch and the power connector to the rear panel of the enclosure.

**Step 14.** Solder the free ends of both black multi‑wire junctions to the ground pin of the power connector, and insulate the joint with electrical tape.

**Step 15.** Solder the shortest red wire (shown in Figure 3) to the power pin of the power connector and the lower pin of the power switch.

**Step 16.** Solder the free end of the upper red multi‑wire junction and the remaining red wire to the upper pin of the power switch. This completes the high‑current power circuit (see [Check 2](#check-2-no-short-circuit-in-the-high-power-circuit) & [Check 3](#check-3-no-reverse-polarity-in-the-high-power-circuit)).

## 5.3 Installing the control-side electronics
**Step 17.** Place the relay board into the enclosure and connect the free end of the bottom red multi‑wire junction to the relay’s NO (Normally Open) terminal.

**Step 18.** Connect the remaining free end of the separate red wire, soldered to the power switch, to the relay’s Common (COM) terminal (see [Check 4](#check-4-powering-up-pwm-modules-and-dc-pumps)).

**Step 19.** Prepare the wire jumpers and remaining wires needed for the device assembly, as shown in Figure 3, using a wire stripper.

Step 20. Mount the screw‑terminal adapter to a side wall of the enclosure using an M6 machine screw inserted into the hole, ensuring that the D12 and D13 labels are oriented at the top so that the Arduino Nano’s D12 pin aligns with the adapter’s D12 terminal. Install the Arduino Nano–compatible board (ATmega328P) into the screw‑terminal adapter.

**Step 21.** Connect the jumper wires to the relay board and secure the free wire ends in the screw‑terminal adapter as shown in Figure 2. For a cleaner layout and easier access to the Arduino and relay, route the red and black wires behind the terminal adapter as shown in Figure 4.

## 5.4 Adding the user interface components
**Step 22.** Solder the LED together with the 220 Ω resistor and the wires as shown in Figure 3.

**Step 23.** Mount the LED to the corresponding hole on the front panel of the enclosure using a hot-glue gun.

**Step 24.** Connect the LED’s wires to the corresponding pins of the screw‑terminal adapter as shown in Figure 2.

**Step 25.** Solder the white and black wires shown in Figure 3B to the push button.

**Step 26.** Install the push button on the front panel using its mounting nut.

**Step 27.** Connect the push button wires to the corresponding pins of the screw‑terminal adapter as shown in Figure 4 (see [Check 5](#check-5-no-wiring-faults-in-the-lowvoltage-control-circuit)).

Figure 4. Top view of the assembled device. 
TODO: ---

## 5.5 Enabling communication with other devices (optional)
**Step 28.** Make an additional rectangular hole on the side panel of the enclosure as shown in Figure 1. 

**Step 29.** Prepare four jumper wires using a wire stripper. Glue the jumper heads together to form a four‑pin female connector as shown in Figure 4, so they remain aligned when inserted into the enclosure.

**Step 30.** Insert the connector into the rectangular hole and secure it to the enclosure wall using a hot‑glue gun.

**Step 31.** Connect the free ends of the connector to the screw‑terminal adapter for communication through either I²C (for GalvaResp; use pins A4 and A5 as shown in Figure 2) or UART (for FireSting; use pins D2 and D3 instead, see Arduino Nano pinmap).

## 5.6 Finalizing the enclosure
**Step 32.** Insert the provided insulating material into the enclosure groove to prevent water contact between the environment and internal wiring.

**Step 33.** Fabricate a water-resistant lid that is attached to the USB cable connected to the Arduino Nano–compatible board (ATmega328P). The lid must fit the opening on the cover of the enclosure and can be made from rubber or another flexible waterproof material.

**Step 34.** Fabricate an additional water‑resistant lid to seal the opening during storage or when the USB cable is removed.

**Step 35.** Screw the cover securely to the enclosure using the original mounting screws.

**Step 36.** Ensure the cover is seated evenly and that no wires are pinched when closing the enclosure.

# 6. Software Setup
This section describes how to program the Arduino Nano and configure the software required to record data from PumpResp. The workflow below reflects the configuration tested and validated for this build.

## 6.1 Installing the Arduino IDE and uploading firmware
PumpResp uses an Arduino Nano microcontroller (original or clone). To load the firmware:

1. Install Arduino IDE version 2.0 or later from the official Arduino website.
2. Connect the Arduino Nano to your PC via USB.
3. In Tools → Board, select Arduino Nano.
4. In Tools → Processor, select ATmega328P (Old Bootloader) if you are using a common Nano clone.
5. Open the provided PumpResp .ino firmware file.
6. Change the variable values for respirometry phases in the user interface according to your experimental design.
7. Click Upload to flash the firmware to the board.

After uploading, the Arduino Nano will begin sending serial data over USB to PC (see [Check 6](#check-6-controlling-pumps-by-arduino-code)).

## 6.2 Configuring the data‑logging software
PumpResp was validated on Windows 10 using Microsoft Excel together with a customized version of the open‑source PLX‑DAQ‑2 macros. This combination provides a straightforward installation process, stable serial communication, direct data logging, and real‑time plotting.

Install Microsoft Excel (version 2016 or newer) if it is not already available on your system. Download the customized PLX‑DAQ‑2 macro file (PumpResp.xlsm) from the repository and extract it to a convenient location on your computer.

PLX‑DAQ‑2 is available only for Windows. Users working on macOS or Linux may employ alternative serial‑logging tools such as CoolTerm or Python with the PySerial library; however, these alternatives were not validated during development and are not covered in this guide.

## 6.3 Establishing the serial connection and recording data
After uploading the firmware (Section 6.1) and preparing the PLX‑DAQ‑2 workbook (Section 6.2), keep the Arduino Nano connected to the computer via USB.
1. Open PumpResp.xlsm in Microsoft Excel.
2. Enable macros when prompted.
3. In the PLX‑DAQ‑2 control panel, select the serial port (COM number) corresponding to the connected Arduino Nano. 
4. Click Connect to open the serial port, initialize communication, and begin writing incoming data directly into the spreadsheet.
5. For improved performance and stability during long recordings, minimize the PLX‑DAQ‑2 control window while data collection is in progress.

## 6.4 Exporting and managing recorded data
When data collection is complete, press Disconnect in the PLX‑DAQ‑2 control panel to close the serial connection. The recorded data remain in the spreadsheet and should be saved at this stage. Export the dataset either as a standard Excel workbook (.xlsx) or as a comma‑separated values file (.csv) for downstream analysis. If the Connect button is pressed again before exporting, the spreadsheet will be cleared and new data will overwrite the previous session. Always save or export the data before reconnecting to avoid accidental data loss (see [Check 7](#check-7-verifying-serial-communication-and-data-logging)).

After completing all assembly and software steps, perform the full‑system validation described in 
(see [Check 8](#check-8-full-system-test-with-submerged-pumps-and-currentdraw-safety)).

# 7. Functional Testing and Verification
This section provides a set of short, targeted functional checks to verify that PumpResp has been assembled correctly and operates safely before experimental use. Each check corresponds to an assembly or software step in Sections 5 and 6. Performing these checks reduces the risk of wiring errors, component damage, and hazardous operating conditions.

### Check 1: Wiring continuity of AMP plugs and PWM modules
Set the multimeter to audible continuity mode; in this mode, it emits a continuous beep when two points are electrically connected. Use the multimeter probes to check continuity between each wire of every AMP plug and the corresponding pin on its PWM module. Perform this for all eight plugs (two wires each). If there is no beep, the wire is not connected to the expected pin.

### Check 2: No short circuit in the high-power circuit
Using the same audible continuity mode, verify that none of the red (power) wires have continuity with the black (ground) wires. Test all accessible points of the multi-wire junction and other soldered connections you can reach with the probes. If the multimeter beeps, a short circuit is present and must be corrected before proceeding.

### Check 3: No reverse polarity in the high-power circuit
Ensure the power switch is in the Off (0) position. Power the device using the 5.5×2.1 mm jack from the power supply unit. Set the multimeter to DC voltage mode and measure the voltage between the power pin of the power connector and any ground point on the black multi‑wire junction. If the measured voltage is negative or significantly different from the rated output voltage of the power supply, the polarity is reversed or the wiring is incorrect and must be fixed before proceeding.

### Check 4: Powering up PWM modules and DC pumps
Ensure the device is powered and the power switch is in the On (1) position. Connect DC pumps with a maximum operating voltage below the rated output of the power supply unit to the AMP plugs. Rotate each PWM knob from its minimum (far left) to maximum (far right) position. Verify that the LED indicator brightens and the pump load increases. If not, replace the PWM module or the DC pump as appropriate.

### Check 5: No wiring faults in the low‑voltage control circuit
Before connecting the Arduino Nano to a USB port, set the multimeter to audible continuity mode and verify that no unintended connections exist between the screw‑terminal adapter pins used for the LED, push button, relay control, and optional communication lines (see Figure 2 and Appendix 1). Confirm that each signal pin (5V, RESET, D4, D5, D12, D13, and optionally A4/D2 and A5/D3) is isolated from ground and from all other signal pins. Any continuity between pins that are not directly wired together in the assembly steps indicates a wiring fault that must be corrected before powering the Arduino.

### Check 6: Controlling Pumps by Arduino code
Upload the Arduino sketch and verify that the pumps and LED respond correctly to the control signals defined in the user interface. Confirm that the lower pump line follows the programmed flow pattern, including the correct duration of the flush phase. Check that the LED indicates system state as intended: it blinks during the measurement phase (flushing pump off) and remains continuously on when the flushing pump is activated.

### Check 7: Verifying serial communication and data logging
After connecting PLX‑DAQ‑2 to the Arduino Nano, confirm that data are being transmitted and recorded correctly. Ensure that the spreadsheet begins populating with time‑stamped entries immediately after pressing Connect, and verify that data continue to append without interruption during the recording period. After pressing Disconnect, check that the recorded dataset remains intact and can be saved or exported without being overwritten.

### Check 8: Full system test with submerged pumps and current‑draw safety
Submerge the pumps in their experimental chambers and run the programmed flow cycle. Adjust pump speeds using the PWM module knobs and confirm that the resulting flow is stable and appropriate for the experiment. Turn the power switch to the Off (0) position. Set the multimeter to current‑measurement mode and place the probes across the two terminals of the power switch to measure the total current draw in series. Verify that the current remains well below the maximum output current of the power supply unit: ideally under 70% of its rated limit. During operation, ensure that the power supply unit becomes only moderately warm and never hot; excessive heating indicates overload or wiring faults that must be corrected before use.

Completing all eight checks ensures that PumpResp is fully functional, electrically safe, and ready for experimental use.

# 8. Appendices
