#include "../src/SettingsManager.h"
#include <Arduino.h>
#include <unity.h>

SettingsManager sm;

void test_ReadSettings(void) {
  UNITY_TEST_ASSERT_EQUAL_INT(SM_SUCCESS, sm.readSettings("/config.json"), __LINE__, "File not in SPIFFS");
  UNITY_TEST_ASSERT_EQUAL_INT(SM_ERROR, sm.readSettings("/NoFile.json"), __LINE__, "File shold not exists");
}

void test_valueType() {
  sm.readSettings("/config.json");
  UNITY_TEST_ASSERT_EQUAL_INT(13, sm.getInt("ledPin"), __LINE__, "Error on getInt");
  UNITY_TEST_ASSERT_EQUAL_INT(13, sm.getInt("ledPin", 99), __LINE__, "Error on getInt with default value");
  UNITY_TEST_ASSERT_EQUAL_INT(99, sm.getInt("noProp", 99), __LINE__, "Error on default value getInt");

  // Serial.println("int ledPin: " + String(sm.getInt("ledPin")));
  // Serial.println("int ledPin: " + String(sm.getInt("ledPin", 99)));
  // Serial.println("int ledPins default: " + String(sm.getInt("ledPins", 99)));

  // Serial.println("uint ledPin: " + String(sm.getUInt("ledPin")));
  // Serial.println("uint ledPin: " + String(sm.getUInt("ledPin", 99)));
  // Serial.println("uint ledPins default: " + String(sm.getUInt("ledPins", 99)));

  // Serial.println("short ledPin: " + String(sm.getShort("ledPin")));
  // Serial.println("short ledPin: " + String(sm.getShort("ledPin", 99)));
  // Serial.println("short ledPins default: " + String(sm.getShort("ledPins", 99)));

  // Serial.println("ushort ledPin: " + String(sm.getUShort("ledPin")));
  // Serial.println("ushort ledPin: " + String(sm.getUShort("ledPin", 99)));
  // Serial.println("ushort ledPins default: " + String(sm.getUShort("ledPins", 99)));

  // Serial.println("long ledPin: " + String(sm.getLong("ledPin")));
  // Serial.println("long ledPin: " + String(sm.getLong("ledPin", 99L)));
  // Serial.println("long ledPins default : " + String(sm.getLong("ledPins", 99L)));

  // Serial.println("ulong ledPin: " + String(sm.getULong("ledPin")));
  // Serial.println("ulong ledPin: " + String(sm.getULong("ledPin", 99L)));
  // Serial.println("ulong ledPins default : " + String(sm.getULong("ledPins", 99L)));
}
void setup() {
  delay(2000);

  UNITY_BEGIN(); // IMPORTANT LINE!
  RUN_TEST(test_ReadSettings);
  RUN_TEST(test_valueType);
  UNITY_END();
}

uint8_t i = 0;
uint8_t max_blinks = 5;

void loop() {
  delay(500);
}