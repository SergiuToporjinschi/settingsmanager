#include "SettingsManager.h"
#define DEBUGER

#ifdef DEBUGER
#define DEBUG_BEGIN Serial.begin(115200)
#else
#define DEBUG_BEGIN
#endif


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(5000);
  SettingsManager sm;
  Serial.println("********************oldFile*********************");
  sm.readSettings(F("/config.json"));
  Serial.println("Default Test: " + sm.getString("wlan", "TTTT") + " - " + sm.getString("wlan"));
  Serial.println("int ledPins: " + String(sm.getLong("ledPins", 23)));
  Serial.println("int ledPins: " + String(sm.getLong("ledPins")));
  //  Serial.println("test: " + sm.getString("ledPin"));
  //  Serial.println("test: " + sm.getString("wlan.ssid"));
  //  Serial.println("test: " + sm.getString("mqtt.internalTopics.settings"));
  //  Serial.println("Defaulttest: " + sm.getString("mqtt.internalTospics.settings"));
  Serial.println("variant: " + sm.getVariant("mqtt.internalTopics.settings").as<String>());
  JsonObject& js = sm.getJsonObject("mqtt.internalTopics");
  js.printTo(Serial);
}

void loop() {
  delay(1000);

  //sm.writeSettings(F("/conf.json"));
  //Serial.println("********************New File*********************");
  //sm.readSettings(F("/conf.json"));
  //  auto settings = sm.getSettings();
  //  Serial.println(SettingsManager::stringify(settings));
  //
  //  sm.setString("test", "testString");
  //  sm.setBool("booleanTest", true);
  //  sm.setInt("intTest", 2333);
  //  sm.writeSettings("/settings.cfg");
  //  auto set = sm.getSettings();
  //  Serial.println(SettingsManager::stringify(set));
}
