#define DEBUGER
#ifdef DEBUGER
#define DBG(x) Serial.print(String("DBG-->") + String(x))
#define DBGLN(x) Serial.println(String("DBG-->") + String(x))
#else
#define DBG(x)
#define DBGLN(x)
#endif

#include "Arduino.h"
#include "SettingsManager.h"
/**
   Reads the content of settings files given by path/name
*/
void SettingsManager::readSettings(String fileName) {
  DBGLN("Reading settings from: " + fileName);
  openSPIFFS();
  File file = SPIFFS.open(fileName, "r");
  if (!file) {
    delay(100);
    DBGLN("Could not open file");
    SPIFFS.end();
    return;
  } else {
    populateSettings(file);
  }
  DBGLN("Closing file");
  file.close();
  SPIFFS.end();
};

/**
   Loads all the settings in current instance
*/
void SettingsManager::populateSettings(File &file) {
  DBGLN("Populate settings");
  root = createJson(getFileContent(file).c_str());
  if (root == 0) {
    DBGLN("Invalid JSON:");
    return;
  }
};

String SettingsManager::getFileContent(File &file) {
  String content, jsonChars = "{},:[]";
  char lastChr;
  while (file.available()) {
    char chr = (char)file.read();
    if ( chr == '\n' || chr == '\r' || chr == '\t' || (jsonChars.indexOf(lastChr) >= 0 && chr == ' ') || (int)chr == 255) {
      continue;
    }
    if (lastChr == ' ' && jsonChars.indexOf(chr) >= 0) {
      content.trim();
    }
    content += chr;
    lastChr = chr;
  }
  content.trim();
  return content;
}

JsonObject* SettingsManager::createJson(const char* payload) {
  DBGLN(payload);
  DynamicJsonBuffer jsonBuffer(1300);
  JsonObject& roots = jsonBuffer.parseObject(payload);
  if (!roots.success()) {
    DBGLN("Invalid JSON:");
    DBGLN(payload);
    return 0;
  }
  return &roots;
}

void SettingsManager::writeSettings(const String & fileName) {
  JsonObject& p =  *root;
  DBGLN("Writing settings to: " + fileName);
  openSPIFFS();
  File file = SPIFFS.open(fileName, "w");
  if (!file) {
    delay(1000);
    DBGLN("Could not write  file");
  } else {
    root->printTo(file);
  }
  DBGLN("Closing file");
  file.close();
  SPIFFS.end();
};

void SettingsManager::openSPIFFS() {
  if (!SPIFFS.begin()) {
    delay(1000);
    DBGLN("Could not mount SPIFFS file system");
  }
};

JsonVariant SettingsManager::getVariant(String key) {
  JsonObject& p = *root;
  JsonVariant item = p;
  String k = key;
  if (key.indexOf('.') > 0) {
    int r = 0, i = 0;
    for (i = 0; i < key.length(); i++ ) {
      if (key[i] == '.') {
        k = key.substring(r, i);
        r = i + 1;
        item = item[k];
        if (!item.success()) {
          DBGLN("Could not find config key: " + key.substring(0, i));
          return "";
        }
      }
    }
    k = key.substring(r, i);
  }
  item = item[k];
  if (!item.success()) {
    DBGLN("Could not find config key: " + key);
  }
  return item;
};

String SettingsManager::getString(String key, String defaultValue) {
  JsonVariant item = getVariant(key);
  Serial.println("DEFAULT: " + defaultValue);
  return item | defaultValue;
};

const char* SettingsManager::getChar(String key, char* defaultValue) {
  JsonVariant item = getVariant(key);
  if (item.success()) {
    return item.as<char*>();
  } else {
    return defaultValue;
  }
};

int SettingsManager::getInt(String key, int defaultValue) {
  JsonVariant item = getVariant(key);
  if (item.success()) {
    return item.as<int>();
  } else {
    return defaultValue;
  }
};

float SettingsManager::getFloat(String key, float defaultValue) {
  JsonVariant item = getVariant(key);
  if (item.success()) {
    return item.as<float>();
  } else {
    return defaultValue;
  }
};

double SettingsManager::getDouble(String key, double defaultValue) {
  JsonVariant item = getVariant(key);
  if (item.success()) {
    return item.as<double>();
  } else {
    return defaultValue;
  }
};

long SettingsManager::getLong(String key, long defaultValue) {
  JsonVariant item = getVariant(key);
  if (item.success()) {
    return item.as<long>();
  } else {
    return defaultValue;
  }
};

bool SettingsManager::getBool(String key, bool defaultValue) {
  JsonVariant item = getVariant(key);
  if (item.success()) {
    return item.as<bool>();
  } else {
    return defaultValue;
  }
};

JsonObject& SettingsManager::getJsonObject(String key) {
  JsonVariant item = getVariant(key);
  return item.as<JsonObject&>();
};

JsonArray& SettingsManager::getJsonArray(String key) {
  JsonVariant item = getVariant(key);
  return item.as<JsonArray&>();
};
