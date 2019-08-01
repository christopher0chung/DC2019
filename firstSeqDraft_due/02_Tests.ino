//---------------------------------------------------------------
//   MODULE TEST STRUCTURES
//---------------------------------------------------------------

int seq[4] = {4, 14, 20, 22};

struct toggler {

	bool tog;
	unsigned int interval;
	unsigned long previousMillis;
	int step;

	void autoTog() {

 		if (millis() - previousMillis >= interval) {

   			previousMillis = millis();

   			nodes[seq[step]].state = 0;
   			leds.drawPixel(nodes[seq[step]].ledx, nodes[seq[step]].ledy, LOW);
   			
   			step++;
   			step = step % 3;
   			
   			nodes[seq[step]].state = 1;
   			leds.drawPixel(nodes[seq[step]].ledx, nodes[seq[step]].ledy, HIGH);

 		}
	}
};

toggler tog = {0, 200};


//---------------------------------------------------------------
//   CONTROLLER TESTS
//---------------------------------------------------------------

void testButtons() {
  
  for (int i = 0; i < 304; i++) {
    
    if (buttons.risingEdge(i)) {
      
        Serial.print("Key");
        Serial.print("\t");
        Serial.print("index:   ");
        Serial.print(i);
        Serial.print("\t");

        String type;
        if (nodes[i].type == 0)
          type = "non-patch";
        else if (nodes[i].type == 1)
          type = "input";
        else if (nodes[i].type == 2)
          type = "special input";
        else if (nodes[i].type == 3)
          type = "output";

        Serial.print(type);
        Serial.println();
      
    }
  }
}


void testPots() {
  for (int i = 0; i < 26; i++) {
    if (pots.hasChanged(i)) {
      Serial.print("Pot");
      Serial.print("\t");
      Serial.print("index:");
      Serial.print(i);
      Serial.print("\t");
      Serial.println(pots.vals[i]);
      pots.updateLastVals(i);
      screenPrint(pots.vals[i]);
    }
  }
}


