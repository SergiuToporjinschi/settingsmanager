/* 

  SettingsManager

  Copyright (C) 2017 by Sergiu Toporjinschi <sergiu dot toporjinschi at gmail dot com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation version 3.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <https://spdx.org/licenses/GPL-3.0-only.html>.

  All rights reserved

*/

#undef UNITY_EXCLUDE_FLOAT

#include "../src/SettingsManager.h"
#include "ArduinoJson.h"
#include <Arduino.h>
#include <unity.h>

SettingsManager sm;


void test_ReadSettings(void) {
  UNITY_TEST_ASSERT_EQUAL_INT(SM_ERROR, sm.readSettings("/NoFile.json"), __LINE__, "File shold not exists");
  UNITY_TEST_ASSERT_EQUAL_INT(SM_SUCCESS, sm.readSettings("/config.json"), __LINE__, "File not in SPIFFS");
  JsonVariant root = sm.getRoot();
  UNITY_TEST_ASSERT(!root.isNull(), __LINE__, "Root object is null");
}

void test_NumericValueType() {
  UNITY_NEW_TEST("getInt");
  UNITY_TEST_ASSERT_EQUAL_INT(13, sm.getInt("ledPin"), __LINE__, "Error on getInt");
  UNITY_TEST_ASSERT_EQUAL_INT(13, sm.getInt("ledPin", 99), __LINE__, "Error on getInt with default value");
  UNITY_TEST_ASSERT_EQUAL_INT(99, sm.getInt("noProp", 99), __LINE__, "Error on default value getInt");

  UNITY_NEW_TEST("getUInt");
  UNITY_TEST_ASSERT_EQUAL_UINT(13, sm.getUInt("ledPin"), __LINE__, "Error on getUInt");
  UNITY_TEST_ASSERT_EQUAL_UINT(13, sm.getUInt("ledPin", 99), __LINE__, "Error on getUInt with default value");
  UNITY_TEST_ASSERT_EQUAL_UINT(99, sm.getUInt("noProp", 99), __LINE__, "Error on default value getUInt");

  UNITY_NEW_TEST("getShort");
  UNITY_TEST_ASSERT_EQUAL_INT(13, sm.getShort("ledPin"), __LINE__, "Error on getShort");
  UNITY_TEST_ASSERT_EQUAL_INT(13, sm.getShort("ledPin", 99), __LINE__, "Error on getShort with default value");
  UNITY_TEST_ASSERT_EQUAL_INT(99, sm.getShort("noProp", 99), __LINE__, "Error on default value getShort");

  UNITY_NEW_TEST("getUShort");
  UNITY_TEST_ASSERT_EQUAL_INT(13, sm.getUShort("ledPin"), __LINE__, "Error on getUShort");
  UNITY_TEST_ASSERT_EQUAL_INT(13, sm.getUShort("ledPin", 99), __LINE__, "Error on getUShort with default value");
  UNITY_TEST_ASSERT_EQUAL_INT(99, sm.getUShort("noProp", 99), __LINE__, "Error on default value getUShort");

  UNITY_NEW_TEST("getLong");
  UNITY_TEST_ASSERT_EQUAL_INT(13, sm.getLong("ledPin"), __LINE__, "Error on getLong");
  UNITY_TEST_ASSERT_EQUAL_INT(13, sm.getLong("ledPin", 99), __LINE__, "Error on getLong with default value");
  UNITY_TEST_ASSERT_EQUAL_INT(99, sm.getLong("noProp", 99), __LINE__, "Error on default value getLong");

  UNITY_NEW_TEST("getULong");
  UNITY_TEST_ASSERT_EQUAL_INT(13, sm.getULong("ledPin"), __LINE__, "Error on getULong");
  UNITY_TEST_ASSERT_EQUAL_INT(13, sm.getULong("ledPin", 99), __LINE__, "Error on getULong with default value");
  UNITY_TEST_ASSERT_EQUAL_INT(99, sm.getULong("noProp", 99), __LINE__, "Error on default value getULong");

#ifndef UNITY_EXCLUDE_DOUBLE
  UNITY_NEW_TEST("getDouble");
  UNITY_TEST_ASSERT_EQUAL_DOUBLE((double)(32.3223), sm.getDouble("doubleTest"), __LINE__, "Error on getDouble");
  UNITY_TEST_ASSERT_EQUAL_DOUBLE((double)(32.3223), sm.getDouble("doubleTest", (double)(75.299)), __LINE__, "Error on getDouble with default value");
  UNITY_TEST_ASSERT_EQUAL_DOUBLE((double)(75.299), sm.getDouble("noProp", (double)(75.299)), __LINE__, "Error on default value getDouble");
#endif

#ifndef UNITY_EXCLUDE_DOUBLE
  UNITY_NEW_TEST("getFloat");
  UNITY_TEST_ASSERT_EQUAL_FLOAT((float)(12.33), sm.getFloat("floatTest"), __LINE__, "Error on getFloat");
  UNITY_TEST_ASSERT_EQUAL_FLOAT((float)(12.33), sm.getFloat("floatTest", (float)(75.299)), __LINE__, "Error on getFloat with default value");
  UNITY_TEST_ASSERT_EQUAL_FLOAT((float)(75.299), sm.getFloat("noProp", (float)(75.299)), __LINE__, "Error on default value getFloat");
#endif
}

void test_BoolValueType() {
  UNITY_NEW_TEST("getBoolean");
  UNITY_TEST_ASSERT(sm.getBool("boolTest"), __LINE__, "Error on getBool");
  UNITY_TEST_ASSERT(sm.getBool("boolTest", "false"), __LINE__, "Error on getBool with default value");
  UNITY_TEST_ASSERT(sm.getBool("boolTest", "true"), __LINE__, "Error on default value getBool");
}

void test_CharValueType() {
  UNITY_NEW_TEST("getCChar");
  UNITY_TEST_ASSERT_EQUAL_INT('t', sm.getCChar("charTest"), __LINE__, "Error on getCChar");
  UNITY_TEST_ASSERT_EQUAL_INT('t', sm.getCChar("charTest", 'H'), __LINE__, "Error on getCChar with default value");
  UNITY_TEST_ASSERT_EQUAL_INT('H', sm.getCChar("noProp", 'H'), __LINE__, "Error on default value getCChar");

  UNITY_NEW_TEST("getSChar");
  UNITY_TEST_ASSERT_EQUAL_INT('T', sm.getSChar("charTestN"), __LINE__, "Error on getSChar");
  UNITY_TEST_ASSERT_EQUAL_INT('T', sm.getSChar("charTestN", 'H'), __LINE__, "Error on getSChar with default value");
  UNITY_TEST_ASSERT_EQUAL_INT('H', sm.getSChar("noProp", 'H'), __LINE__, "Error on default value getSChar");

  UNITY_NEW_TEST("getUChar");
  UNITY_TEST_ASSERT_EQUAL_INT('T', sm.getUChar("charTestN"), __LINE__, "Error on getUChar");
  UNITY_TEST_ASSERT_EQUAL_INT('T', sm.getUChar("charTestN", 'H'), __LINE__, "Error on getUChar with default value");
  UNITY_TEST_ASSERT_EQUAL_INT('H', sm.getUChar("noProp", 'H'), __LINE__, "Error on default value getUChar");

  UNITY_NEW_TEST("getCharFromPath");
  UNITY_TEST_ASSERT_NOT_NULL(sm.getChar("wlan.hostName"), __LINE__, "NullVal");
  UNITY_TEST_ASSERT_EQUAL_STRING("hostName of esp", sm.getChar("wlan.hostName"), __LINE__, "Error on getCharFromPath");
  UNITY_TEST_ASSERT_EQUAL_STRING("hostName of esp", sm.getChar("wlan.hostName", "defaultHostName"), __LINE__, "Error on getCharFromPath with default value");
  UNITY_TEST_ASSERT_EQUAL_STRING("defaultHostName", sm.getChar("noProp", "defaultHostName"), __LINE__, "Error on default value getCharFromPath");

  UNITY_NEW_TEST("getStringFromPath");
  UNITY_TEST_ASSERT_EQUAL_STRING("hostName of esp", sm.getString("wlan.hostName").c_str(), __LINE__, "Error on getStringFromPath");
  UNITY_TEST_ASSERT_EQUAL_STRING("hostName of esp", sm.getString("wlan.hostName", "defaultHostName").c_str(), __LINE__, "Error on getStringFromPath with default value");
  UNITY_TEST_ASSERT_EQUAL_STRING("defaultHostName", sm.getString("noProp.noProp", "defaultHostName").c_str(), __LINE__, "Error on default value getStringFromPath");

  UNITY_NEW_TEST("getChar");
  UNITY_TEST_ASSERT_EQUAL_STRING("url for update", sm.getChar("updateServer"), __LINE__, "Error on getChar");
  UNITY_TEST_ASSERT_EQUAL_STRING("url for update", sm.getChar("updateServer", "defaultValue"), __LINE__, "Error on getChar");
  UNITY_TEST_ASSERT_EQUAL_STRING("defaultValue", sm.getChar("noProp", "defaultValue"), __LINE__, "Error on getChar");

  UNITY_NEW_TEST("getStringFromRoot");
  UNITY_TEST_ASSERT_EQUAL_STRING("url for update", sm.getString("updateServer").c_str(), __LINE__, "Error on getStringFromRoot");
  UNITY_TEST_ASSERT_EQUAL_STRING("url for update", sm.getString("updateServer", "defaultValue").c_str(), __LINE__, "Error on getStringFromRoot");
  UNITY_TEST_ASSERT_EQUAL_STRING("defaultValue", sm.getString("noProp", "defaultValue").c_str(), __LINE__, "Error on getStringFromRoot");
}

void test_LoadJsonFromString() {
  UNITY_NEW_TEST("loadJson");
  UNITY_TEST_ASSERT_EQUAL_INT(SM_ERROR, sm.loadJson("{\"testInLoadingJson\":\"this is a string value\",\"Level1\":{{\"Level2Key\":12,\"Level2Test\":true,\"Level3\":{\"float\":23.5,\"int\":22}}}"), __LINE__, "An invalid Json was loaded");
  UNITY_TEST_ASSERT_EQUAL_INT(SM_SUCCESS, sm.loadJson("{\"testInLoadingJson\":\"this is a string value\",\"Level1\":{\"Level2Key\":12,\"Level2Test\":true,\"Level3\":{\"float\":23.5,\"int\":22}}}"), __LINE__, "Cold not load a valid Json");
  UNITY_TEST_ASSERT_EQUAL_STRING("this is a string value", sm.getString("testInLoadingJson").c_str(), __LINE__, "Error on getString");
  UNITY_TEST_ASSERT_EQUAL_INT(12, sm.getInt("Level1.Level2Key"), __LINE__, "Error on getInt");
  UNITY_TEST_ASSERT_EQUAL_INT(22, sm.getInt("Level1.Level3.int"), __LINE__, "Error on getInt");
  UNITY_TEST_ASSERT(sm.getInt("Level1.Level2Test"), __LINE__, "Error on getBool");
}

void test_writeJson() {
  UNITY_NEW_TEST("writeJson");
  UNITY_TEST_ASSERT_EQUAL_INT(12, sm.getInt("Level1.Level2Key"), __LINE__, "Error on getInt");
  UNITY_TEST_ASSERT_EQUAL_INT(SM_SUCCESS, sm.loadJson("{\"newProp\":\"newProp value\"}"), __LINE__, "Could not load a valid json");
  UNITY_TEST_ASSERT_EQUAL_INT(5, sm.getInt("Level1.Level2Key", 5), __LINE__, "Error on loading prop");
  UNITY_TEST_ASSERT_EQUAL_INT(SM_SUCCESS, sm.writeSettings("/config1.json"), __LINE__, "Could not save a valid json");
  UNITY_TEST_ASSERT_EQUAL_INT(SM_SUCCESS, sm.readSettings("/config1.json"), __LINE__, "Could not load a valid json");

  UNITY_TEST_ASSERT_EQUAL_STRING("newProp value", sm.getString("newProp", "failed").c_str(), __LINE__, "Error on loading prop");
  UNITY_TEST_ASSERT_EQUAL_INT(SM_SUCCESS, sm.readSettings("/config.json"), __LINE__, "Could not load a valid json");
  UNITY_TEST_ASSERT_EQUAL_STRING("failed", sm.getString("newProp", "failed").c_str(), __LINE__, "Error on loading prop");
}

void setup() {
  delay(2000);
  UNITY_BEGIN();
  RUN_TEST(test_ReadSettings);
  RUN_TEST(test_BoolValueType);
  RUN_TEST(test_NumericValueType);
  RUN_TEST(test_CharValueType);
  RUN_TEST(test_LoadJsonFromString);
  RUN_TEST(test_writeJson);
  UNITY_END();
}

void loop() {
  delay(500);
}