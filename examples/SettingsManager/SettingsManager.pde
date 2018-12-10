#include "SettingsManager.h"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  delay(5000);
  SettingsManager sm;
  sm.readSettings("/settings.cfg");
  auto settings = sm.getSettings();
  Serial.println(SettingsManager::stringify(settings));
  Serial.println("********************save process*********************");

  sm.setString("test", "testString");
  sm.setBool("booleanTest", true);
  sm.setInt("intTest", 2333);
  sm.writeSettings("/settings.cfg");
  auto set = sm.getSettings();
  Serial.println(SettingsManager::stringify(set));
  Serial.println("********************end save process*********************");
}
