#include "macros.h"
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
  sm.readSettings("/config.json");


  //  Serial.println("Default Test: " + sm.getString("wlan", "TTTT") + " - " + sm.getString("wlan"));
  Serial.println("long ledPins: " + String(sm.getLong("ledPins", 23L)));
  Serial.println("long ledPins: " + String(sm.getLong("ledPin", 23L)));
  Serial.println("short ledPins: " + String(sm.getShort("ledPin", 23)));
  Serial.println("int ledPins: " + String(sm.getInt("ledPin", 23L)));
  Serial.println("char ledPins: " + String(sm.getChar("ledPin", 'H')));

  Serial.println("int ledPins: " + String(sm.getInt("ledPin", 23L)));
  Serial.println("int process.interval: " + String(sm.getInt("process.interval", -1)));

  //  Serial.println("int ledPins: " + String(sm.getLong("ledPins")));
  //  Serial.println("test: " + sm.getString("ledPin"));
  //  Serial.println("test: " + sm.getString("wlan.ssid"));
  //  Serial.println("test: " + sm.getString("mqtt.internalTopics.settings"));
  //  Serial.println("Defaulttest: " + sm.getString("mqtt.internalTospics.settings"));

  JsonObject vr = sm.getJsonVariant("mqtt.status");
  if (!vr.isNull()) {
    serializeJsonPretty(vr, Serial);
    DBGLN("");
  } else {
    DBGLN("no variant");
  }

  JsonObject ob = sm.getJsonObject("mqtt.status");
  if (!ob.isNull()) {
    serializeJsonPretty(ob, Serial);
    DBGLN("");
  } else {
    DBGLN("no ob");
  }
  //  JsonObject& js = sm.getJsonObject("mqtt.internalTopics");
  //  serializeJson(js, Serial);
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
