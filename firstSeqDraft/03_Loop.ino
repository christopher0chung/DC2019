

void loop() {
  pots.update();
  //keysUpdate();

  timerUpdate();

  //  ledsUpdate will write the entire model. Excessive write operations may
  //    be present as a consequence.  Potential area for performance
  //    optimization.
  
  ledsUpdate();
  leds.write();
}
