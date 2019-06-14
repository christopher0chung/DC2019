void setup() {
  Serial.begin(9600);
  ledsInit();
  potsInit(); 
  keysInit();

  c1.changeState(Forward, Forward);
}
