void turnOn(int slice) {
  digitalWrite(slice, HIGH);
}
void turnOff(int slice) {
  digitalWrite(slice, LOW);
}
void turnOnAll() {
  for (int i = 0; i < 8; i++) {
    turnOn(allPins[i]);
  }
}
void turnOffAll() {
  for (int i = 0; i < 8; i++) {
    turnOff(allPins[i]);
  }
}
void animateReset() {
  for (int i = 0; i < 20; i++) {
    turnOnAll();
    delay(100);
    turnOffAll();
    delay(100);
  }
}
void animateRotation() {
  turnOffAll();
  for (int i = 0; i < 8; i++) {
    turnOn(allPins[i]);
    delay(100);
  }
  for (int i = 0; i < 8; i++) {
    turnOff(allPins[i]);
    delay(100);
  }
}
void animateSlice(int slice) {
  turnOffAll();
  for (int i = 0; i < 8; i++) {
    if (i != 0) {
      turnOff(allPins[i - 1]);
    }
    turnOn(allPins[i]);
    delay(100);
  }

  turnOffAll();
  for (int i = 0; i < 8; i++) {
    if (i != 0) {
      turnOff(allPins[i - 1]);
    }
    turnOn(allPins[i]);
    delay(100);
  }

  turnOffAll();
  for (int i = 1; i <= slice; i++) {
    turnOn(allPins[i - 1]);
    delay(100);
  }
}
void freePizzaAnimate() {
  turnOffAll();

  for (int i = 0; i < 10; i++) {
    turnOn(allPins[0]);
    turnOn(allPins[7]);
    delay(100);

    turnOff(allPins[0]);
    turnOff(allPins[7]);
    turnOn(allPins[1]);
    turnOn(allPins[6]);
    delay(100);

    turnOff(allPins[1]);
    turnOff(allPins[6]);
    turnOn(allPins[2]);
    turnOn(allPins[5]);
    delay(100);

    turnOff(allPins[2]);
    turnOff(allPins[5]);
    turnOn(allPins[3]);
    turnOn(allPins[4]);
    delay(100);

    turnOff(allPins[3]);
    turnOff(allPins[4]);
    turnOn(allPins[2]);
    turnOn(allPins[5]);
    delay(100);

    turnOff(allPins[2]);
    turnOff(allPins[5]);
    turnOn(allPins[1]);
    turnOn(allPins[6]);
    delay(100);

    turnOff(allPins[1]);
    turnOff(allPins[6]);
    turnOn(allPins[0]);
    turnOn(allPins[7]);
    delay(100);
  }
}
void animateProp() {
  turnOffAll();
  for (int i = 0; i < 19; i++) {
    int ledDelay = 200 - (100 * (i * 0.1));

    turnOn(allPins[0]);
    turnOn(allPins[2]);
    turnOn(allPins[5]);
    delay(ledDelay);
    turnOn(allPins[1]);
    turnOn(allPins[3]);
    turnOn(allPins[6]);

    turnOff(allPins[0]);
    turnOff(allPins[2]);
    turnOff(allPins[5]);
    delay(ledDelay);
    turnOn(allPins[2]);
    turnOn(allPins[4]);
    turnOn(allPins[7]);

    turnOff(allPins[1]);
    turnOff(allPins[3]);
    turnOff(allPins[6]);
    delay(ledDelay);
    turnOff(allPins[2]);
    turnOff(allPins[4]);
    turnOff(allPins[7]);
  }

  int randomNum = random(1, 8);
  turnOffAll();
  for (int i = 0; i < 8; i++) {
    turnOn(allPins[i]);
    delay(30);
  }
  for (int i = 0; i < 8; i++) {
    turnOff(allPins[i]);
    delay(30);
  }

  turnOn(allPins[randomNum]);
}
