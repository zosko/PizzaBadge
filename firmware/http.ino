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
          animateRotation();
          animateSlice(payload.toInt());
        }
      }
    } else {
      Serial.printf("[HTTP] failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}
