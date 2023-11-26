// Version 1.1

////////////////////
// USER INTERFACE //
////////////////////

// Set the length of measurement and flush phases (in seconds)
int FLUSH = 5;        // LED is on, flushing pump is on
int MEASUREMENT = 15; // LED is blinking, flushing pump is off

// By default, the relay is active low. 
// Thus, if your relay is active high, reverse the variable values:
const byte RELAY_ON = LOW;
const byte RELAY_OFF = HIGH;

/////////////////////////
// IMPLEMENTATION CODE //
/////////////////////////

int LED = 5;
int RELAY = 3;
int PERIOD = 1;

void setup()
{
   pinMode(RELAY, OUTPUT);
   pinMode(LED, OUTPUT);
   Serial.begin(9600);
   Serial.println("CLEARRANGE,A,2,E,1000000"); // to get rid of AM-PM
   Serial.println((String) "LABEL, Date,Time,Phase,Millis");
}

void loop()
{
   digitalWrite(RELAY, RELAY_OFF); // set pin 3 OFF to turn off the relay,
                                  // so pumps start working again.

   for(int counter = 0; counter < FLUSH; counter++)
      {
         Serial.println((String) "DATA,DATE,TIME," + (String)"F"+PERIOD+(",") + millis());
         digitalWrite(LED, HIGH);
         delay(1000);
      }

   digitalWrite(RELAY, RELAY_ON); // set pin 3 ON to activate the relay,
                              // so pumps stop working

   for(int counter = 0; counter < MEASUREMENT; counter++)
      {
         Serial.println((String) "DATA,DATE,TIME," + (String)"M"+PERIOD+(",") + millis());
         digitalWrite(LED, HIGH);
         delay(200);
         digitalWrite(LED, LOW);
         delay(800);
      }

    PERIOD++;
}
