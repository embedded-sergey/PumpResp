# PumpResp
The pump controller for intermittent‐flow aquatic respirometry. 
It is a part of the FishResp project (more information about 
the project and installation instructions at https://fishresp.org)

PumpResp.ino should be uploaded to Arduino Uno or Nano.
To do so, go through the following steps:
1) download, install and open Arduino IDE (https://www.arduino.cc/en/software)
2) connect the pump controller to a computer using a USB cable.
3) click "Tools" in the main bar of Arduino IDE, select "Board" 
and choose "Arduino Nano"
4) click "Tools" in the main bar of Arduino IDE, select "Processor" 
and choose "Atmega328P (Old Bootloader)"
5) click "Tools" in the main bar of Arduino IDE, select "Port" and 
choose an available USB port which is connected to the pump regulator.
6) create a new sketch, copy the code from the file "PumpResp.ino".
7) change time for "flush" and "measurement" phases in the “User Inteface” 
(time is in seconds)
8) click the “upload” button (right arrow icon).

PumpResp.xlsm is required for logging data to PC (only Windows). 
The file is based on the "PLX-DAQ version 2" software
(https://forum.arduino.cc/index.php?topic=437398.0). In the PLX-DAQ 
interface, select the correct port to which Arduino is connected 
and press the button "Connect". When an experiment is over, press 
the button "Disconnect" and save as a separate .txt file. Then close 
it without saving.
