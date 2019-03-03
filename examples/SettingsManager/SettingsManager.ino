/*

  SerialTrigger 0.1.0

  SerialTrigger

  Copyright (C) 2017 by Sergiu Toporjinschi <sergiu dot toporjinschi at gmail dot com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  dependency:
  ArduinoJson: https://arduinojson.org/
  
*/


#include "SettingsManager.h"

#define DEBUGER
#ifdef DEBUGER
#define DEBUG_BEGIN Serial.begin(115200)
#else
#define DEBUG_BEGIN
#endif

SettingsManager sm;
void setup() {
  delay(5000);
}
void getTests() {
  // put your setup code here, to run once:
  sm.readSettings("/config.json");

  Serial.println("int ledPin: " + String(sm.getInt("ledPin", 99)));
  Serial.println("int ledPins default: " + String(sm.getInt("ledPins", 99)));
  Serial.println("uint ledPin: " + String(sm.getUInt("ledPin", 99)));
  Serial.println("uint ledPins default: " + String(sm.getUInt("ledPins", 99)));

  Serial.println("short ledPin: " + String(sm.getShort("ledPin", 99)));
  Serial.println("short ledPins default: " + String(sm.getShort("ledPins", 99)));
  Serial.println("ushort ledPin: " + String(sm.getUShort("ledPin", 99)));
  Serial.println("ushort ledPins default: " + String(sm.getUShort("ledPins", 99)));

  Serial.println("long ledPin: " + String(sm.getLong("ledPin", 99L)));
  Serial.println("long ledPins default : " + String(sm.getLong("ledPins", 99L)));
  Serial.println("ulong ledPin: " + String(sm.getULong("ledPin", 99L)));
  Serial.println("ulong ledPins default : " + String(sm.getULong("ledPins", 99L)));

  Serial.print("CChar charTest: "); Serial.println(sm.getCChar("charTest", 'H'));
  Serial.print("CChar charTests default: "); Serial.println(sm.getCChar("charTests", 'H'));

  Serial.print("char charTestN: "); Serial.println(sm.getChar("charTestN", 'H'));
  Serial.print("char charTestNs default: "); Serial.println(sm.getChar("charTestNs", 'H'));
  Serial.print("uchar charTestN: "); Serial.println(sm.getUChar("charTestN", 'H'));
  Serial.print("uchar charTestNs default: "); Serial.println(sm.getUChar("charTestNs", 'H'));

  Serial.println("char * wlan.hostName: " + String(sm.getChar("wlan.hostName", "defaHostName")));
  Serial.println("char * wlan.hostName default: " + String(sm.getChar("wlan.hostNames", "defaHostName")));

  Serial.println("String wlan.hostName: " + sm.getString("wlan.hostName", "defaHostName"));

  Serial.println("float floatTest: " + String(sm.getFloat("floatTest", 19.2F)));
  Serial.println("float floatTests default : " + String(sm.getFloat("floatTests", 19.2F)));

  Serial.println("double doubleTest: " + String(sm.getDouble("doubleTest", 75.299D)));
  Serial.println("double doubleTests default : " + String(sm.getDouble("doubleTests", 75.299D)));

  Serial.println("bool boolTest: " + String(sm.getBool("boolTest", true)));
  Serial.println("bool boolTests default : " + String(sm.getBool("boolTests", false)));

  Serial.println("Test getJsonVariant");
  JsonObject vr = sm.getJsonVariant("mqtt.status");
  if (!vr.isNull()) {
    serializeJsonPretty(vr, Serial);
    Serial.println("");
  } else {
    Serial.println("no variant");
  }

  Serial.println("Test getJsonObject");
  JsonObject ob = sm.getJsonObject("mqtt.internalTopics");
  if (!ob.isNull()) {
    serializeJsonPretty(ob, Serial);
    Serial.println("");
  } else {
    Serial.println("getTests: no ob");
  }
}

void setTest() {
  Serial.println ("should increment LedPin int");
  sm.readSettings("/config.json");
  int res = sm.setString("updateServer", "Other Test");
  Serial.print("WriteResult:"); Serial.println(res);
  sm.setInt("ledPin", 15);
  sm.writeSettings("/config.json");
}

void readWriteTest() {
  Serial.println ("should increment LedPin int");
  sm.readSettings("/config.json");
  int pin = sm.getInt("ledPin");
  Serial.print("read value:"); Serial.println(pin);
  sm.setInt("ledPin", ++pin);
  sm.writeSettings("/config.json");
}

void loadSettingsTest() {
  sm.loadJson("{\"testInLoadingJson\":\"this is a string value\",\"Level1\":{\"Level2Key\":12,\"Level2Test\":true,\"Level3\":{\"float\":23.5}}}");
  JsonObject ob = sm.getRoot();
  if (!ob.isNull()) {
    serializeJsonPretty(ob, Serial);
    Serial.println("");
  } else {
    Serial.println("loadSetti: no ob");
  }
  Serial.println("String testInLoadingJson: " + sm.getString("testInLoadingJson"));
  Serial.println("int Level1.Level2Key: " + String(sm.getInt("Level1.Level2Key", 199)));
  Serial.println("double Level1.Level3.float: " + String(sm.getDouble("Level1.Level3.float", 75.299D)));
  Serial.println("bool Level1.Level2Test: " + String(sm.getBool("Level1.Level2Test", true)));
}

void loop() {
  //  delay(1000);
  //  setTest();
  delay(1000);
  getTests();
  delay(1000);
  readWriteTest();
  delay(1000);
  loadSettingsTest();
}
