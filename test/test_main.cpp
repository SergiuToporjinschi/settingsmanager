#undef UNITY_EXCLUDE_FLOAT

#include "../src/SettingsManager.h"
#include <Arduino.h>
#include <unity.h>


SettingsManager sm;

void test_ReadSettings(void) {
  UNITY_TEST_ASSERT_EQUAL_INT(SM_SUCCESS, sm.readSettings("/config.json"), __LINE__, "File not in SPIFFS");
  UNITY_TEST_ASSERT_EQUAL_INT(SM_ERROR, sm.readSettings("/NoFile.json"), __LINE__, "File shold not exists");
}

void test_NumericValueType() {
  UNITY_NEW_TEST("getInt")  ;
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

  UNITY_NEW_TEST("getChar");    
  UNITY_TEST_ASSERT_NOT_NULL(sm.getChar("wlan.hostName"), __LINE__, "NullVal");
  UNITY_TEST_ASSERT_EQUAL_STRING("hostName of esp", sm.getChar("wlan.hostName"), __LINE__, "Error on getChar");
  UNITY_TEST_ASSERT_EQUAL_STRING("hostName of esp", sm.getChar("wlan.hostName", "defaultHostName"), __LINE__, "Error on getChar with default value");
  UNITY_TEST_ASSERT_EQUAL_STRING("defaultHostName", sm.getChar("noProp", "defaultHostName"), __LINE__, "Error on default value getChar");

  UNITY_NEW_TEST("getString");    
  UNITY_TEST_ASSERT_EQUAL_STRING("hostName of esp", sm.getString("wlan.hostName").c_str(), __LINE__, "Error on getString");
  UNITY_TEST_ASSERT_EQUAL_STRING("hostName of esp", sm.getString("wlan.hostName", "defaultHostName").c_str(), __LINE__, "Error on getString with default value");
  UNITY_TEST_ASSERT_EQUAL_STRING("defaultHostName", sm.getString("noProp", "defaultHostName").c_str(), __LINE__, "Error on default value getString");
}

void setup() {
  delay(2000);
  UNITY_BEGIN(); // IMPORTANT LINE!
  RUN_TEST(test_ReadSettings);
  RUN_TEST(test_BoolValueType);
  RUN_TEST(test_NumericValueType);
  RUN_TEST(test_CharValueType);
  UNITY_END();
}

uint8_t i = 0;
uint8_t max_blinks = 5;

void loop() {
  delay(500);
}