#include "ArduinoJson.h"
#include "SettingsManager.h"
#include "unity.h"

SettingsManager sm;
const char *content = "{\"testInLoadingJson\":\"this is a string value\",\"charTest\": \"t\",\"Level1\":{\"Level2KeyLong\":2147483640,\"Level2KeyLongNeg\":-2147483640, \"Level2Key\":12,\"Level2KeyNeg\":-12, \"charTest\": \"t\",\"Level2Test\":true,\"Level3\":{\"float\":23.5}}}";

void testLoadJson(void) {
  sm.loadJson(content);
  JsonObject root = sm.getRoot();
  TEST_ASSERT_NOT_NULL(&root);
  TEST_ASSERT_FALSE(root.isNull());
  TEST_ASSERT_EQUAL_UINT(3, root.size());
}

void testString(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_STRING(String("this is a string value").c_str(), sm.getString("testInLoadingJson").c_str());
}

void testStringDefault(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_STRING(String("this does not exists").c_str(), sm.getString("notAValidKey", "this does not exists").c_str());
}

void testStringNegative(void) {
  sm.loadJson(content);
  String nullVal = sm.getString("notAValidKey");
  TEST_ASSERT_NULL(nullVal);
}

void testJsonObject(void) {
  sm.loadJson(content);
  JsonObject obj = sm.getJsonObject("Level1");
  TEST_ASSERT_NOT_NULL(&obj);
  TEST_ASSERT_FALSE(obj.isNull());
}

void testJsonObjectNegative(void) {
  sm.loadJson(content);
  JsonObject obj = sm.getJsonObject("LevelNotExisiting");
  TEST_ASSERT_NOT_NULL(&obj);
  TEST_ASSERT_TRUE(obj.isNull());
}

void testJsonVariant(void) {
  sm.loadJson(content);
  JsonVariant obj = sm.getJsonVariant("Level1");
  TEST_ASSERT_NOT_NULL(&obj);
  TEST_ASSERT_FALSE(obj.isNull());
}

void testJsonVariantNegative(void) {
  sm.loadJson(content);
  JsonVariant obj = sm.getJsonVariant("LevelNotExisiting");
  TEST_ASSERT_NOT_NULL(&obj);
  TEST_ASSERT_TRUE(obj.isNull());
}

void testInt(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT((int)(12), sm.getInt("Level1.Level2Key"));
}

void testIntNeg(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT((int)(-12), sm.getInt("Level1.Level2KeyNeg"));
}

void testIntNegDefault(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT((int)(-13), sm.getInt("Level1.Level2KeyNeg_", -13));
}

void testIntDefault(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT((int)(13), sm.getInt("Level1.Level2Key_", 13));
}

void testIntNegative(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT((int)(0), sm.getInt("Level1.Level2Key_"));
}

void testUInt(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT((unsigned int)(12), sm.getUInt("Level1.Level2Key"));
}

void testUIntDefault(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT((unsigned int)(13), sm.getUInt("Level1.Level2Key_", 13));
}

void testUIntNegative(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT((unsigned int)(0), sm.getUInt("Level1.Level2Key_"));
}

void testSInt(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT((signed short)(12), sm.getShort("Level1.Level2Key"));
}

void testSIntDefault(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT((signed short)(13), sm.getShort("Level1.Level2Key_", 13));
}

void testSIntNegative(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT((signed short)(0), sm.getShort("Level1.Level2Key_"));
}

void testUShort(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT((unsigned short)(12), sm.getUShort("Level1.Level2Key"));
}

void testUShortDefault(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT((unsigned short)(13), sm.getUShort("Level1.Level2Key_", 13));
}

void testUShortNegative(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT((unsigned short)(0), sm.getUShort("Level1.Level2Key_"));
}

void testLong(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT32((signed long)(2147483640), sm.getLong("Level1.Level2KeyLong"));
}

void testLongNeg(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT32((signed long)(-2147483640), sm.getLong("Level1.Level2KeyLongNeg"));
}

void testLongNegDefault(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT32((signed long)(-2147483641), sm.getLong("Level1.Level2KeyLongNeg_", (signed long)(-2147483641)));
}

void testLongDefault(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT32((signed long)(2147483641), sm.getLong("Level1.Level2KeyLong_", (signed long)(2147483641)));
}

void testLongNegative(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT32((signed long)(0), sm.getLong("Level1.Level2KeyLong_"));
}

void testULong(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT32((unsigned long)(2147483640), sm.getULong("Level1.Level2KeyLong"));
}

void testULongDefault(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT32((unsigned long)(2147483640), sm.getULong("Level1.Level2KeyLong_", (unsigned long)(2147483640)));
}

void testULongNegDefault(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT32((unsigned long)(-2147483641), sm.getULong("Level1.Level2KeyLongNeg_", (unsigned long)(-2147483641)));
}

void testULongNegative(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT32((unsigned long)(0), sm.getULong("Level1.Level2KeyLong_"));
}

void testCChar(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT8('t', sm.getCChar("Level1.charTest"));
}

void testCCharDefault(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT8('r', sm.getCChar("Level1.charTest_", 'r'));
}

void testUChar(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT8((unsigned char)(116), sm.getCChar("Level1.charTest"));
}

void testUCharDefault(void) {
  sm.loadJson(content);
  TEST_ASSERT_EQUAL_INT8((unsigned char)(117), sm.getCChar("Level1.charTest_", (unsigned char)(117)));
}

void setup() {
  delay(2000);
}

void loop() {
  UNITY_BEGIN();
  RUN_TEST(testLoadJson);

  RUN_TEST(testString);
  RUN_TEST(testStringDefault);
  RUN_TEST(testStringNegative);

  RUN_TEST(testInt);
  RUN_TEST(testIntNeg);
  RUN_TEST(testIntDefault);
  RUN_TEST(testIntNegDefault);
  RUN_TEST(testIntNegative);

  RUN_TEST(testUInt);
  RUN_TEST(testUIntDefault);
  RUN_TEST(testUIntNegative);

  RUN_TEST(testSInt);
  RUN_TEST(testSIntDefault);
  RUN_TEST(testSIntNegative);

  RUN_TEST(testUShort);
  RUN_TEST(testUShortDefault);
  RUN_TEST(testUShortNegative);

  RUN_TEST(testLong);
  RUN_TEST(testLongNeg);
  RUN_TEST(testLongDefault);
  RUN_TEST(testLongNegDefault);
  RUN_TEST(testLongNegative);

  RUN_TEST(testULong);
  RUN_TEST(testULongDefault);
  RUN_TEST(testULongNegative);
  RUN_TEST(testULongNegDefault);

  RUN_TEST(testCChar);
  RUN_TEST(testCCharDefault);

  RUN_TEST(testUChar);
  RUN_TEST(testUCharDefault);

  RUN_TEST(testJsonObject);
  RUN_TEST(testJsonObjectNegative);
  RUN_TEST(testJsonVariant);
  RUN_TEST(testJsonVariantNegative);
  UNITY_END();
}