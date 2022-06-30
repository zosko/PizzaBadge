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

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  WiFi.mode(WIFI_STA);

  for (int i = 0; i < 8; i++) {
    pinMode(allPins[i], OUTPUT);
  }
  turnOffAll();

  wm.setTitle("Pizza Badge");

  const char* custom_server_str = "<br/><label for='customfieldid'>Enter Email</label><input type='text' name='customfieldid'>";
  new (&custom_field) WiFiManagerParameter(custom_server_str);
  wm.addParameter(&custom_field);
  wm.setSaveParamsCallback(saveParamCallback);

  std::vector<const char *> wm_menu  = {"wifi"};
  wm.setShowInfoUpdate(false);
  wm.setShowInfoErase(false);
  wm.setMenu(wm_menu);

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

  // SMD version > 1000
  // Normal version < 1000
  if (analogRead(pin_reset) > 1000) { 
    animateReset();
    factoryReset();
  }
}
