////////////////////
// USER INTERFACE //
////////////////////

// Set the length of measurement and flush phases (in seconds)
int FLUSH = 5;       // LED is on
int MEASUREMENT = 15; // LED is blinking

/////////////////////////
// IMPLEMENTATION CODE //
/////////////////////////

// Include Arduino Wire library for I2C protocol
#include <Wire.h>
#define PumpResp_address 99 // define I2C address for PumpResp
#define PumpResp_size 5  // define the maximum size of 'Phase' string from PumpResp

int LED = 4;
int RELAY = 5;
int PERIOD = 1;
String phase, F, M, f = "F", m = "M";

void setup(){
   pinMode(RELAY, OUTPUT); 
   pinMode(LED, OUTPUT);
   
   Wire.begin(PumpResp_address);  // initialize I2C communications, slave/server mode
   Wire.onRequest(requestEvent);  // function to run when data requested from SensResp
   Wire.onReceive(receiveEvent);  // function to run when data received from SensResp
   
   Serial.begin(9600); // start the serial communication to the PC/SensResp
   Serial.println("CLEARRANGE,A,2,E,1000000"); // trick to get rid of AM-PM
   Serial.println((String) "LABEL, Date,Time,Phase,Millis"); // print the header of Excel sheet
}

void receiveEvent(){
  // Read while data received
  while (Wire.available() > 0) {
    byte x = Wire.read();
  }
}

void requestEvent(){
  // Setup byte variable in the correct size
  byte PumpResp_response[PumpResp_size];
  
  // Format the phase string as an array
  for (byte i=0;i<PumpResp_size;i++) {
    PumpResp_response[i] = (byte)phase.charAt(i);
  }
  
  // Send response back to SensResp
  Wire.write(PumpResp_response,sizeof(PumpResp_response));
}

void loop(){
   pinMode(RELAY, LOW); // set pin 3 OFF to turn off the relay,
                        // so pumps start working again.
                        
   for(int counter = 0; counter < FLUSH; counter++){       
         F = f + PERIOD;
         Serial.println((String) "DATA,DATE,TIME," + F +(",") + millis());
         digitalWrite(LED, HIGH);
         delay(1000); 
         phase = F;
      }

   pinMode(RELAY, HIGH); // set pin 3 ON to activate the relay,
                         // so pumps stop working
                         
   for(int counter = 0; counter < MEASUREMENT; counter++){      
         M = m + PERIOD;
         Serial.println((String) "DATA,DATE,TIME," + M +(",") + millis());
         digitalWrite(LED, HIGH);
         delay(200); 
         digitalWrite(LED, LOW);
         delay(800); 
         phase = M;
      }      
   
   PERIOD++;
}       

// Sources:
// 1. I2C mode instructions: https://dronebotworkshop.com/i2c-arduino-arduino/
