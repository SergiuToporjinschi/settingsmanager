/*

  SettingsManager

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

#include "debug_macro.h"
#ifdef DEBUGGER 
Print *dbg = &Serial;
#endif

#include "Macro.h"
#include "SettingsManager.h"
#include <Arduino.h>

SettingsManager sm;

void printSettings() {
  JsonObject ob = sm.getRoot();
  if (!ob.isNull()) {
    serializeJsonPretty(ob, Serial);
    Serial.println("");
  }
}

void readChangeSave() {
  Serial.println("---------- Read settings from file ----------");
  sm.readSettings("/config.json");
  Serial.println("---------- Current settings ----------");
  printSettings();

  Serial.println("---------- Change settings ----------");
  sm.loadJson("{\"testInLoadingJson\":\"this is a string value\",\"Level1\":{\"Level2Key\":12,\"Level2Test\":true,\"Level3\":{\"float\":23.5}}}");
  Serial.println("---------- Save settings ----------");
  sm.writeSettings("/config.json");

  Serial.println("---------- Read settings from file ----------");
  sm.readSettings("/config.json");
  Serial.println("---------- Settings in the file ----------");
  printSettings();
}

void testStringIntBoolFloat() {
  Serial.println("---------- Current settings ----------");
  printSettings();
  Serial.println("---------- Change something ----------");

  sm.setString("testInLoadingJson", "the NewString");
  sm.setInt("Level1.Level2Key", (int)(99));
  sm.setBool("Level1.Level2Test", (bool)(0));
  sm.setFloat("Level1.Level3.float", (float)(99.9));

  Serial.println("---------- Save settings ----------");
  sm.writeSettings("/config.json");
  Serial.println("---------- Read settings from file ----------");
  sm.readSettings("/config.json");
  Serial.println("---------- New settings content ----------");
  printSettings();
}

void testReplaceStructure() {
  Serial.println("---------- Current settings ----------");
  printSettings();
  Serial.println("---------- Change something ----------");

  sm.setString("testInLoadingJson", "the NewString");
  sm.setInt("Level1.Level2Key", (int)(99));
  sm.setBool("Level1.Level2Test", (bool)(0));
  sm.setDouble("Level1.Level3", (double)(99.99));

  Serial.println("---------- Save settings ----------");
  sm.writeSettings("/config.json");
  Serial.println("---------- Read settings from file ----------");
  sm.readSettings("/config.json");
  Serial.println("---------- New settings content ----------");
  printSettings();
}

void testAddNonExistingNodesInStructure() {
  Serial.println("---------- Current settings ----------");
  printSettings();
  Serial.println("---------- Change something ----------");

  sm.setString("*RootKey", "the NewString in root");
  sm.setInt("**RootKey", (int)(22));
  sm.setInt("*Level1.*Level2Key", (int)(100));
  sm.setBool("Level1.*Level2Test", (bool)(1));
  sm.setDouble("*Level1.*Level3", (double)(100.101));

  Serial.println("---------- Not added if not existing ----------");
  sm.setDouble("#Level1.#Level3", (double)(100.101), false);

  Serial.println("---------- Save settings ----------");
  sm.writeSettings("/config.json");
  Serial.println("---------- Read settings from file ----------");
  sm.readSettings("/config.json");
  Serial.println("---------- New settings content ----------");
}

void setup() {
  delay(5000);
  Serial.begin(74800);

  Serial.println("********** [ Read Change Save ]**********");
  readChangeSave();
  Serial.println();
  Serial.println();
  Serial.println();

  sm.loadJson("{\"testInLoadingJson\":\"this is a string value\",\"Level1\":{\"Level2Key\":12,\"Level2Test\":true,\"Level3\":{\"float\":23.5}}}");
  Serial.println(sm.getString("testInLoadingJson.otherstaff.other", "test"));
  Serial.println();
  Serial.println();
  Serial.println();
  printSettings();

  Serial.println("********** [ String int bool float ]**********");
  testStringIntBoolFloat();
  Serial.println();
  Serial.println();
  Serial.println();

  Serial.println("********** [ Change Structure ]**********");
  testReplaceStructure();
  Serial.println();
  Serial.println();
  Serial.println();

  Serial.println("********** [ Add Nonexisting nodes in Structure ]**********");
  testAddNonExistingNodesInStructure();
  printSettings();

  Serial.println("********** [ END ] **********");
}

void loop() {
  delay(100);
}
