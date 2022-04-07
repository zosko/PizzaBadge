void writeCodeToEEPROM(const String &strToWrite) {
  byte len = strToWrite.length();
  EEPROM.write(0, len);
  for (int i = 0; i < len; i++) {
    EEPROM.write(1 + i, strToWrite[i]);
  }
  if (EEPROM.commit()) {
    Serial.println("EEPROM successfully committed");
  } else {
    Serial.println("ERROR! EEPROM commit failed");
  }
}
String readCodeFromEEPROM() {
  int newStrLen = EEPROM.read(0);
  char data[newStrLen + 1];

  for (int i = 0; i < newStrLen; i++) {
    data[i] = EEPROM.read(1 + i);
  }
  data[newStrLen] = '\0';
  return String(data);
}
