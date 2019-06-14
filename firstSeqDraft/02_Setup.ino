void setup() {
  Serial.begin(9600);
  ledsInit();
  potsInit();
  keysInit();

  //  changeState must be called at the beginning before any updates.
  //  This is called in setup() and not the constructor, because the constructor
  //    does not permit internal function calls because they are not yet defined
  //    and as such, modulo value assignment would have to be redundantly coded
  //    in the constructor in addition to meaningfully residing in 'changeState'.

  c1.changeState(PingPong, PingPong);

  delay(2000);
}
