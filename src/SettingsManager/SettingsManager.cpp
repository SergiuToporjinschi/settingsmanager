#include "Arduino.h"
#include "SettingsManager.h"

/**
   Reads the content of settings files given by path/name
*/
void SettingsManager::readSettings(char * fileName) {
  DBGF("Reading settings from: %s", fileName);
  openSPIFFS();
  File file = SPIFFS.open(fileName, "r");
  if (!file) {
    DBGLN("Could not open file");
    SPIFFS.end();
    return;
  } else {
    char js[JSON_LEN] = {0};
    getFileContent(js, file);
    Serial.println("s");
    Serial.println(js);
    createJson(js);
  }
  DBGLN("Closing file");
  file.close();
  SPIFFS.end();
}

void SettingsManager::writeSettings(const char * fileName) {
  DBGF("Writing settings to: %s", fileName);
  openSPIFFS();
  File file = SPIFFS.open(fileName, "w");
  if (!file) {
    DBGLN("Could not write  file");
  } else {
    char buff[JSON_LEN] = {0};
    size_t len = measureJsonPretty(root) + 1;
    serializeJsonPretty(root, buff, len);
    file.print(buff);
    file.flush();
  }
  DBGLN("Closing file");
  file.close();
  SPIFFS.end();
}

void SettingsManager::getFileContent(char* content, File &file) {
  char jsonChars[7] = "{},:[]";
  char lastChr;
  int len = 0;
  while (file.available()) {
    char chr = (char)file.read();
    if (chr == '\n' || chr == '\r' || chr == '\t' || (strchr(jsonChars, lastChr) != NULL && chr == ' ') || (int) chr == 255) {
      continue;
    }
    if ((int)lastChr == 32 && strchr(jsonChars, chr) != NULL) {
      content[strlen(content) - 1] = '\000';
    }
    content[strlen(content)] = chr;
    content[strlen(content) + 1] = '\000';
    lastChr = chr;
  }
}

void SettingsManager::createJson(const char* payload) {
  DeserializationError err = deserializeJson(doc, payload);
  if (err) {
    DBGLN("Invalid JSON:");
    return;
  }
  root = doc.as<JsonObject>();
}

void SettingsManager::openSPIFFS() {
  if (!SPIFFS.begin()) {
    delay(100);
    DBGLN("Could not mount SPIFFS file system");
  }
}

JsonVariant SettingsManager::getJsonVariant(const char * key) {
  if (root.containsKey(key)) {
    return root.getMember(key);
  }
  char _key[100] = {0};
  strcpy(_key, key);

  char * k = strchr(_key, '.');
  if (k == nullptr) {
    Serial.print("Key not found:"); Serial.println(key);
    JsonVariant vr;
    return vr;
  }
  char * crs = &_key[0];
  JsonVariant node = root;
  while (k != nullptr) {
    k[0] = '\0';
    if ( strlen(crs) > 0) {
      node = node.getMember(crs);
    }
    k++;
    crs = k;
    k = strchr(crs, '.');
    if (k == nullptr) {
      node = node.getMember(crs);
      break;
    }
  }
  return node;
};

JsonObject SettingsManager::getJsonObject(const char * key) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<JsonObject>();
  } else {
    JsonObject obj;
    return obj;
  }
}

JsonArray SettingsManager::getJsonArray(const char * key) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<JsonArray>();
  } else {
    JsonArray arr;
    return arr;
  }
}

signed int SettingsManager::getInt(const char * key, const signed int defaultValue) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<signed int>();
  } else {
    return defaultValue;
  }
}

unsigned int SettingsManager::getUInt(const char * key, const unsigned int defaultValue) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<unsigned int>();
  } else {
    return defaultValue;
  }
}

signed short SettingsManager::getShort(const char * key, const signed short defaultValue = 0) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<signed short>();
  } else {
    return defaultValue;
  }
}

unsigned short SettingsManager::getUShort(const char * key, const unsigned short defaultValue = 0) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<unsigned short>();
  } else {
    return defaultValue;
  }
}

signed long SettingsManager::getLong(const char * key, const signed long defaultValue = 0L) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<signed long>();
  } else {
    return defaultValue;
  }
}

unsigned long SettingsManager::getULong(const char * key, const unsigned long defaultValue = 0L) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<unsigned long>();
  } else {
    return defaultValue;
  }
}

char SettingsManager::getCChar(const char * key, const char defaultValue = '\0') {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    const char * x = item.as<const char*>();
    return x[0];
  } else {
    return defaultValue;
  }
}

signed char SettingsManager::getChar(const char * key, const signed char defaultValue = '\0') {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<signed char>();
  } else {
    return defaultValue;
  }
}

unsigned char SettingsManager::getUChar(const char * key, const unsigned char defaultValue = '\0') {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<unsigned char>();
  } else {
    return defaultValue;
  }
}

const char * SettingsManager::getChar(const char * key, const char * defaultValue = "") {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<char*>();
  } else {
    return defaultValue;
  }
}

String SettingsManager::getString(const char * key, const String defaultValue = "") {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<String>();
  } else {
    return defaultValue;
  }
}

float SettingsManager::getFloat(const char * key, const float defaultValue = 0.0F) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<float>();
  } else {
    return defaultValue;
  }
}

double SettingsManager::getDouble(const char * key, const double defaultValue = 0) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<double>();
  } else {
    return defaultValue;
  }
}

bool SettingsManager::getBool(const char * key, const bool defaultValue = false) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<bool>();
  } else {
    return defaultValue;
  }
}

int SettingsManager::setInt(const char * key, const signed int value) {
  JsonVariant item = getJsonVariant(key);
  if (item.isNull()) {
    return SM_KEY_NOT_FOUND;
  } else {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  }
}

int SettingsManager::setUInt(const char * key, const unsigned int value) {
  JsonVariant item = getJsonVariant(key);
  if (item.isNull()) {
    return SM_KEY_NOT_FOUND;
  } else {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  }
}

int SettingsManager::setShort(const char * key, const signed short value) {
  JsonVariant item = getJsonVariant(key);
  if (item.isNull()) {
    return SM_KEY_NOT_FOUND;
  } else {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  }
}

int SettingsManager::setUShort(const char * key, const unsigned short value) {
  JsonVariant item = getJsonVariant(key);
  if (item.isNull()) {
    return SM_KEY_NOT_FOUND;
  } else {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  }
}

int SettingsManager::setLong(const char * key, const signed long value) {
  JsonVariant item = getJsonVariant(key);
  if (item.isNull()) {
    return SM_KEY_NOT_FOUND;
  } else {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  }
}

int SettingsManager::setULong(const char * key, const unsigned long value) {
  JsonVariant item = getJsonVariant(key);
  if (item.isNull()) {
    return SM_KEY_NOT_FOUND;
  } else {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  }
}

int SettingsManager::setCChar(const char * key, const char value) {
  JsonVariant item = getJsonVariant(key);
  if (item.isNull()) {
    return SM_KEY_NOT_FOUND;
  } else {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  }
}

int SettingsManager::setChar(const char * key, const signed char value) {
  JsonVariant item = getJsonVariant(key);
  if (item.isNull()) {
    return SM_KEY_NOT_FOUND;
  } else {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  }
}

int SettingsManager::setUChar(const char * key, const unsigned char value) {
  JsonVariant item = getJsonVariant(key);
  if (item.isNull()) {
    return SM_KEY_NOT_FOUND;
  } else {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  }
}

int SettingsManager::setChar(const char * key, const char * value) {
  JsonVariant item = getJsonVariant(key);
  if (item.isNull()) {
    return SM_KEY_NOT_FOUND;
  } else {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  }
}

int SettingsManager::setString(const char * key, const String value) {
  JsonVariant item = getJsonVariant(key);
  if (item.isNull()) {
    return SM_KEY_NOT_FOUND;
  } else {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  }
}

int SettingsManager::setFloat(const char * key, const float value) {
  JsonVariant item = getJsonVariant(key);
  if (item.isNull()) {
    return SM_KEY_NOT_FOUND;
  } else {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  }
}

int SettingsManager::setDouble(const char * key, const double value) {
  JsonVariant item = getJsonVariant(key);
  if (item.isNull()) {
    return SM_KEY_NOT_FOUND;
  } else {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  }
}

int SettingsManager::setBool(const char * key, const bool value) {
  JsonVariant item = getJsonVariant(key);
  if (item.isNull()) {
    return SM_KEY_NOT_FOUND;
  } else {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  }
}
