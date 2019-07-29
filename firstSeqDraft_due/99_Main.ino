

void setup() {

//  Serial.begin(9600);
  potsInit();
  ledsInit();
  screenInit();
  linksInit();
  currentGlobalMode = LIVEPATCH;
}

void loop() {

  buttons.update();
  pots.update();
  linkStateUpdate();

  tog1.autoTog();


  for (int i = 0; i < buttonsMax; i++) 
    leds.drawPixel(nodes[i].ledx, nodes[i].ledy, nodes[i].state);

  if (currentGlobalMode == PERFORM) {

		// autoTog();
		// commandLeft();
		// commandPots();

  } 
  else if (currentGlobalMode == LIVEPATCH || currentGlobalMode == EDITPATCH) {
  	
  	readButtons();

  } 

// testButtons();
// testPots();



  buttons.updateLastVals(); 
  leds.write();

}
