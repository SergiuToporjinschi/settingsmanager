#include "macros.h"
#include "SettingsManager.h"
#define DEBUGER

#ifdef DEBUGER
#define DEBUG_BEGIN Serial.begin(115200)
#else
#define DEBUG_BEGIN
#endif

SettingsManager sm;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(5000);

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

}

void loop() {
  int pin = sm.getInt("ledPin");
  sm.setInt("ledPin", pin);
  delay(1000);
  Serial.println("modified ledPins: " + String(sm.getInt("ledPin")));
  delay(1000);
  sm.writeSettings("/config.json");
  delay(1000);
}
