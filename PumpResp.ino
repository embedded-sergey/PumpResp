// Version 1.0

////////////////////
// USER INTERFACE //
////////////////////

// Set the length of measurement and flush phases (in seconds)
int FLUSH = 4;       // LED is on, flushing pump is on
int MEASUREMENT = 4; // LED is blinking, flushing pump is off

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
   digitalWrite(RELAY, LOW); // set pin 3 OFF to turn off the relay,
                        // so pumps start working again.

   for(int counter = 0; counter < FLUSH; counter++)
      {
         Serial.println((String) "DATA,DATE,TIME," + (String)"F"+PERIOD+(",") + millis());
         digitalWrite(LED, HIGH);
         delay(1000);
      }

   digitalWrite(RELAY, HIGH); // set pin 3 ON to activate the relay,
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
