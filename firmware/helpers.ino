void saveParamCallback() {
  webURLParam = getParam("customfieldid");
  Serial.println("PARAM customfieldid = " + webURLParam);
  shouldSaveConfig = true;
}
String getParam(String name) {
  String value;
  if (wm.server->hasArg(name)) {
    value = wm.server->arg(name);
  }
  return value;
}
void factoryReset() {
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
