struct flibbity {
  int myIntArray[5];

  void init (int toIngest[]) {
    for (int i = 0; i < 5; i++)
      myIntArray[i] = toIngest[i];
  }

  void printItAll() {
    for (int i = 0; i < 5; i++) {
      Serial.println(myIntArray[i]);
    }
  }
};

int arrayOfIntsToPass[5] = {0, 1, 2, 3, 4};

flibbity newFlib;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  newFlib.init(arrayOfIntsToPass);
}

void loop() {
  // put your main code here, to run repeatedly:
  newFlib.printItAll();
}
