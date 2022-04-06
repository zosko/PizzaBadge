#include <WiFiManager.h>
#include <EEPROM.h>
#include <ESP8266HTTPClient.h>

const int pin_reset = A0;
const int pin_slice_1 = D1;
const int pin_slice_2 = D2;
const int pin_slice_3 = D3;
const int pin_slice_4 = D4;
const int pin_slice_5 = D5;
const int pin_slice_6 = D6;
const int pin_slice_7 = D7;
const int pin_slice_8 = D8;

const int allPins[8] = { pin_slice_1, pin_slice_2, pin_slice_3, pin_slice_4,
                         pin_slice_5, pin_slice_6, pin_slice_7, pin_slice_8
                       };

WiFiManager wm;
WiFiManagerParameter custom_field;
bool shouldSaveConfig = false;
String webURLParam = "";

void saveParamCallback() {
  webURLParam = getParam("customfieldid");
  Serial.println("PARAM customfieldid = " + webURLParam);
  shouldSaveConfig = true;
}
String getParam(String name) {
  //read parameter from server, for customhmtl input
  String value;
  if (wm.server->hasArg(name)) {
    value = wm.server->arg(name);
  }
  return value;
}
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
void checkForPizzaPoint() {
  WiFiClient client;
  HTTPClient http;
  if (http.begin(client, "http://192.168.31.86:8080/check/" + webURLParam)) {
    int httpCode = http.GET();
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.print("Payload:");
        Serial.println(payload);
        if (payload.toInt() > 0 && payload.toInt() < 9) {
          turnOffAll();
          turnOn(allPins[payload.toInt() - 1]);
        }
      }
    } else {
      Serial.printf("[HTTP] failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}
void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  WiFi.mode(WIFI_STA);

  for (int i = 0; i < 7; i++) {
    pinMode(allPins[i], OUTPUT);
  }
  turnOffAll();

  const char* custom_server_str = "<br/><label for='customfieldid'>Enter Badge Code</label><input type='text' name='customfieldid' maxlength='5'>";
  new (&custom_field) WiFiManagerParameter(custom_server_str);
  wm.addParameter(&custom_field);
  wm.setSaveParamsCallback(saveParamCallback);

  bool res;
  res = wm.autoConnect("PizzaBadgeAP");

  if (!res) {
    Serial.println("Failed to connect");
  }
  else {
    Serial.println("connected...yeey :)");
    if (shouldSaveConfig) {
      writeCodeToEEPROM(webURLParam);
      delay(100);
    }
    webURLParam = readCodeFromEEPROM();
    delay(100);
    Serial.print("LOADED FROM EEPROM:[");
    Serial.print(webURLParam);
    Serial.println("]");
  }

  pinMode(pin_reset, INPUT_PULLUP);
}

void loop() {
  checkForPizzaPoint();
  delay(5000);

  if (analogRead(pin_reset) > 1000) {
    Serial.println("RESET");
    animateReset();
    WiFi.mode(WIFI_STA);
    delay(1000);
    WiFi.disconnect();
    delay(1000);
    wm.resetSettings();
    delay(1000);
    ESP.eraseConfig();
    delay(1000);
    ESP.reset();
    delay(1000);
    ESP.restart();
    delay(1000);
  }
}
