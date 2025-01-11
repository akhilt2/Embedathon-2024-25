#include <Preferences.h>

Preferences preferences;

void setup() {
  Serial.begin(115200);

  if (!preferences.begin("Passwords", false)) {
    Serial.println("There is no Passwords namespace.");
    return;
  }

  String outputmsg = "";

  for (int i = 0; i <= 6; i++) {
    String key = "line" + String(i);
    String line = preferences.getString(key.c_str(), "");

    if (line.isEmpty()) continue;
    outputmsg += line + "\n";
  }

  Serial.println("Extracted Message:");
  Serial.println(outputmsg);

  preferences.end();
}

void loop() {
}
