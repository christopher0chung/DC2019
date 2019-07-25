

void setup() {
  //  Serial.begin(9600);
  potsInit();
  ledsInit();
  screenInit();
}

void loop() {

  buttons.update();
  pots.update();
      testButtons();
  //    testPots();
//  autoTog();
//  commandLeft();
//
//  
//  comSwitchUpdate();



  
  leds.write();

}
