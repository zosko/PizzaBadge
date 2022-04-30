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
