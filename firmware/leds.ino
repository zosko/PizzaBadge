void turnOn(int slice) {
  digitalWrite(slice, HIGH);
}
void turnOff(int slice) {
  digitalWrite(slice, LOW);
}
void turnOnAll() {
  for (int i = 0; i < 7; i++) {
    turnOn(allPins[i]);
  }
}
void turnOffAll() {
  for (int i = 0; i < 7; i++) {
    turnOff(allPins[i]);
  }
}
void animateReset() {
  for (int i = 0; i < 50; i++) {
    turnOnAll();
    delay(100);
    turnOffAll();
    delay(100);
  }
}
