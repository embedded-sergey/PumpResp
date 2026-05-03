---
title: "PumpResp Build Guide"
author: "Sergey Morozov"
date: "12 April 2026"
revision: "0.3"
toc: true
toc-depth: 3
---

# PumpResp Build Guide
**Revision:** 0.3  
**Author:** Sergey Morozov  
**Date:** 12 April 2026

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

PumpResp is an open‑source device for controlling pumps and recording pump‑phase data used in intermittent‑flow respirometry. It can operate up to eight 5–24 V DC pumps and can transmit data to a computer over USB. The device can also communicate with external dissolved‑oxygen meters to enable threshold‑based pump activation in addition to simple time‑based control.

This guide explains how to assemble the hardware step by step. It covers preparing the enclosure, wiring the electronics, installing the user‑interface components, and loading the software. The document focuses strictly on construction and verification; experimental applications and biological context are described separately in the accompanying manuscript.

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

The power supply unit must include integrated overcurrent protection (fuse or electronic limit) and should be selected based on the total power requirements of the connected pumps. For example, if eight pumps each draw 0.3 A at 12 V, the total current is 2.4 A. In this case, a 12 V, 4 A power supply provides sufficient overhead for safe operation (i.e., operating below ~70% of the PSU’s maximum rated output). The minimum recommended wire size for regular 5-12V is 24 AWG and 20 AWG for high‑current pump circuits.

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
## 5.1 Preparing the enclosure
1. Unscrew the cover to open the enclosure.
2. Mark out the hole positions on the base and on the cover of the enclosure using a ruler and a pencil, as shown in Figure 1.
3. If you use components with different form factors, or if you use an enclosure with different dimensions, adjust the blueprint accordingly or mark out the positions on the fly.
4. Drill the holes in the marked layout on the enclosure, then adjust the hole geometry using a utility cutter. 
5. For oval‑shaped holes on the rear panel, drill two overlapping holes and shape the opening with a cutter or a rotary tool, including the top recess.
6. Assemble eight male waterproof connectors with 8 cm wires (if not preassembled).
7. Remove the two protrusions on the rear side of each male waterproof connector using a rotary tool with a sanding disk.
8. Insert the waterproof connectors into the oval‑shaped holes and secure them to the enclosure wall using a hot‑glue gun.

*Figure 1*. Blueprint of the PumpResp enclosure:

TODO: add the top recess and increase power whole

## 5.2 Installing power distribution components
9. Mount the PWM controllers to the front panel of the enclosure.
10. Connect the male waterproof connector wires to the Power (+) and Power (–) terminals of the corresponding PWM controller located in front of the connector.
11. Assemble the wire combination by soldering the wire bundles as shown in Figure 2A. Insulate all exposed solder joints with electrical tape to ensure no bare wires remain.
12. Connect the red wires to the Motor (+) and the black wires to the Motor (–) terminals of each PWM controller as illustrated in Figure 2B.
13. Mount the rocker power switch and the power connector to the rear panel of the enclosure.
14. Solder the free ends of both black wire combinations to the ground pin of the power connector, and insulate the joint with electrical tape.
15. Solder both separate red wires shown in Figure 2B to the power pin of the power connector. Then solder the other end of the shorter red wire to the lower pin of the power switch.
16. Solder the free end of the bottom red wire combination to the upper pin of the power switch. This completes the high‑current power circuit.

## 5.3 Installing the control-side electronics
17. Place the relay board into the enclosure and connect the free end of the top red wire combination to the relay’s NO (Normally Open) terminal.
18. Connect the remaining free end of the separate wire, soldered to the power connector, to the relay’s COM (Common) terminal.
19. Prepare the wire jumpers and remaining wires needed for the device assembly, as shown in Figure 3A, using a wire stripper.
20. Mount the screw‑terminal adapter to a side wall of the enclosure using an M6 machine screw inserted into the hole. Install the Arduino Nano–compatible board (ATmega328P) into the screw‑terminal adapter.
21. Connect the jumper wires to the relay board and secure the free wire ends in the screw‑terminal adapter as shown in Figure 4A.

## 5.4 Adding the user interface components
22. Solder the LED together with the 220 Ω resistor and the wires as shown in Figure 3B.
23. Mount the LED to the corresponding hole on the front panel of the enclosure using a hot-glue gun.
24. Connect the LED’s wires to the corresponding pins of the screw‑terminal adapter as shown in Figure 4B.
25. Solder the white and black wires shown in Figure 3B to the push button.
26. Install the push button on the front panel using its mounting nut.
27. Connect the push button wires to the corresponding pins of the screw‑terminal adapter as shown in Figure 4C.

## 5.5 Enabling communication with other devices (optional)
28. Make an additional rectangular hole on the side panel of the enclosure as shown in Figure 5A. 
29. Prepare four jumper wires using a wire stripper. Glue the jumper heads together forming a four-pin female connector as shown in Figure 5B to maintain alignment when inserting into the enclosure.
30. Insert the connector into the rectangular hole and secure it to the enclosure wall using a hot‑glue gun.
31. Connect the free ends of the connector to the screw‑terminal adapter for communication through either UART for GalvaResp or I2C for FireSting as shown in Figure 5C and Figure 5D, respectively.

## 5.6 Finalizing the enclosure
32. Insert the provided insulating material into the enclosure groove to prevent water contact between the environment and internal wiring.
33. Fabricate a water-resistant lid that is attached to the USB cable connected to the Arduino Nano–compatible board (ATmega328P). The lid must fit the opening on the cover of the enclosure and can be made from rubber or another flexible waterproof material.
34. Fabricate an additional water‑resistant lid to seal the opening during storage or when the USB cable is removed.
35. Screw the cover securely to the enclosure using the original mounting screws.
36. Ensure the cover is seated evenly and no wires are pinched.

# 6. Software Setup
This section describes how to program the Arduino Nano and configure the software required to record data from PumpResp. The workflow below reflects the configuration tested and validated for this build.

## 6.1 Installing the Arduino IDE and uploading firmware
PumpResp uses an Arduino Nano microcontroller (original or clone). To load the firmware:

1. Install Arduino IDE 2.x from the official Arduino website.
2. Connect the Arduino Nano to your PC via USB.
3. In Tools → Board, select Arduino Nano.
4. In Tools → Processor, select ATmega328P (Old Bootloader) if you are using a common Nano clone.
5. Open the provided PumpResp .ino firmware file.
6. Change the variable values for respirometry phases in the user interface according to your experimental design.
7. Click Upload to flash the firmware to the board.

After uploading, the Arduino Nano will begin sending serial data over USB to PC.

## 6.2 Configuring the data‑logging software
PumpResp was validated on Windows 10 using Microsoft Excel together with a customized version of the open‑source PLX‑DAQ‑2 macros. This combination provides a straightforward installation process, stable serial communication, direct data logging, and real‑time plotting.

Install Microsoft Excel (version 2016 or newer) if it is not already available on your system. Download the customized PLX‑DAQ‑2 macro file (PumpResp.xlsm) from the repository and extract it to a convenient location on your computer.

PLX‑DAQ‑2 is available only for Windows. Users working on macOS or Linux may employ alternative serial‑logging tools such as CoolTerm or Python with the PySerial library; however, these alternatives were not validated during development and are not covered in this guide.

## 6.3 Establishing the serial connection and recording data
After uploading the firmware (Section 6.1) and preparing the PLX‑DAQ‑2 workbook (Section 6.2), keep the Arduino Nano connected to the computer via USB.
1. Open PumpResp.xlsm in Microsoft Excel.
2. Enable macros when prompted.
3. In the PLX‑DAQ‑2 control panel, select the serial port (COM number) corresponding to the connected Arduino Nano. 
4. Click Connect to open the serial port, initialize communication, and begin writing incoming data directly into the spreadsheet, with real‑time plots updating automatically if they are enabled.
5. For improved performance and stability during long recordings, minimize the PLX‑DAQ‑2 control window while data collection is in progress.

## 6.4 Exporting and managing recorded data
When data collection is complete, press Disconnect in the PLX‑DAQ‑2 control panel to close the serial connection. The recorded data remain in the spreadsheet and should be saved at this stage. Export the dataset either as a standard Excel workbook (.xlsx) or as a comma‑separated values file (.csv) for downstream analysis. If the Connect button is pressed again before exporting, the spreadsheet will be cleared and new data will overwrite the previous session. Always save or export the data before reconnecting to avoid accidental data loss.

# 7. Functional Testing and Verification

# 8. Appendices
