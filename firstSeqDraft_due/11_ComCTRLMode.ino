//---------------------------------------------------------------
//   VARIABLES
//---------------------------------------------------------------

String screenComCtrl[5] = {"VEL", "LEN", "PICH", "CC", " "};


//---------------------------------------------------------------
//   FUNCTIONS
//---------------------------------------------------------------

void comCtrlSelect() {

	int comCtrlInputs[4] = {285, 301, 302, 296};

  	for (int i = 0; i < 4; i++) {

      	if (buttons.risingEdge(comCtrlInputs[i])) {

      		nodes[comCtrlInputs[comCtrlMode]].state = 0;

        	if (comCtrlMode == i) 
	          comCtrlMode = 4;  
	        else {
	          nodes[comCtrlInputs[i]].state = 1;
	          comCtrlMode = i;
	        }

	        comCtrlModeNode = comCtrlInputs[i];
	        screenPrint(screenComCtrl[i]);

	    }
  	}
}


void comCtrlUpdate() {

	int comCtrlpots[4] = {21, 15, 22, 20};
  	
  	for (int i = 0; i < 4; i++) {

    	if (pots.hasChanged(comCtrlpots[i])) {

			int potReading = pots.vals[comCtrlpots[i]];    

	      	switch (comCtrlMode) {

		        case 0: {
		            int vel = potReading;
		            vel = map(vel, 0, 150, 0, 127);
		            vel = constrain(vel, 0, 127);

		            if (vel != velAdjust[i]) {
			            velAdjust[i] = vel;
			            screenPrint(vel);
		            }
		            break;
		        }
		        

		        case 1: {
		            unsigned int noteLength = potReading;
		            noteLength = map(noteLength, 0, 150, 10, 3000);
		            noteLength = constrain(noteLength, 10, 3000);

		            if (noteLength != lengthAdjust[i]) {
			            lengthAdjust[i] = noteLength;
			            screenPrint(noteLength);
		            }

		            break;
		       	}


		        case 2: {
		            int adj = potReading;
		            adj = map(adj, 0, 150, -24, 24);
		            adj = constrain(adj, -24, 24);

		            if (adj != pitchAdjust[i]) {
			            pitchAdjust[i] = adj;
			            screenPrint(adj);
		            }

		            break;
		        }
		        

		        case 3: {
		            int ccVal = potReading;
		            ccVal = map(ccVal, 0, 150, 0, 127);
		            ccVal = constrain(ccVal, 0, 127);

		            if (ccVal != lastccVal[i]) {
			        	usbMIDI.sendControlChange(20 + i, ccVal, 1);
			            lastccVal[i] = ccVal;
			            screenPrint(ccVal);
		            }
		        
		        	break;
				}


		        case 4: {
		        	break;
		        }
	      	}
    	}
  	}
}
