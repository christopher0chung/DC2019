#include <CD4067.h>                    

MuxIn pots(14, 15, 16, 17, 1);           // Modi Matrix(pcbA, pcbB, pcbC, toggleSmoothing)  

void setup() {   
  pots.attach(A6);      
  pots.attach(A7);  
  pots.smoothAmount = .9;                                     
  Serial.begin(9600);              // Begin Serial communication
}

void loop() {
  pots.refresh();                               // REQUIRED TO RECEIVE UPDATED READINGS
  
  for (int x=0; x<pots.numMux; x++) {           // Loop through the rows. numMux is equal to the number of times attach() is called in setup
    Serial.print(x);                            // Print row number at start of every line
    Serial.print(" : \t");
    for (int y=0; y<muxChannels; y++) {         // Nested loop through the columns
      Serial.print(pots.getReading(x, y));      // Print the reading at (x, y) coordinates
      Serial.print("\t");                       // Tab to create space between readings
    }
    Serial.println();                           // New line for next row of readings
  }
  
  delay(100);                                   // Makes easier to read serial monitor
}
