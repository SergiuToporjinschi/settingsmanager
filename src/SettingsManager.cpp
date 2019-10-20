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

#include "SettingsManager.h"
#include "debug_macro.h"
#ifdef ARDUINO_ARCH_ESP32
#  include "SPIFFS.h"
#endif
#ifdef ARDUINO_ARCH_ESP8266
#  include "FS.h"
#endif

/**
    Reads the content of settings file given by path/name
*/
int SettingsManager::readSettings(const char *fileName) {
  DBGLN("Reading settings from: %s", fileName);
  unsigned int loaded = SM_SUCCESS;
  openSPIFFS();
  File file = SPIFFS.open(fileName, "r");
  if (!file) {
    DBGLN("Could not open file");
    SPIFFS.end();
    loaded = SM_ERROR;
  } else {
    char js[JSON_LEN] = {0};
    getFileContent(js, file);
    loaded = loadJson(js);
    file.close();
    SPIFFS.end();
  }
  DBGLN("Closing file");
  return loaded;
}

/**
    Writes the content of settings to a file given by path/name
*/
int SettingsManager::writeSettings(const char *fileName) {
  return writeSettings(fileName, doc.as<JsonVariant>());
}

/**
    Writes the content of settings to a file given by path/name
*/
int SettingsManager::writeSettings(const char *fileName, JsonVariant conf) {
  DBGLN("Writing settings to: %s", fileName);
  openSPIFFS();

  File file = SPIFFS.open(fileName, "w");
  if (!file) {
    DBGLN("Could not write in file");
    SPIFFS.end();
    return SM_ERROR;
  } else {
    serializeJson(conf, file);
    delay(1000);
    DBGLN("File written");
  }
  file.close();
  SPIFFS.end();
  DBGLN("File and SPIFFS closed");
  return SM_SUCCESS;
}

/**
   Reads the file content
*/
void SettingsManager::getFileContent(char *content, File &file) {
  char jsonChars[7] = "{},:[]";
  char lastChr = '\0';
  while (file.available()) {
    char chr = (char)file.read();
    if (chr == 10 || chr == '\r' || chr == '\t' || (strchr(jsonChars, lastChr) != NULL && chr == ' ') || (int)chr == 255) {
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

/**
   Loads a json and is stored in json structure
*/
int SettingsManager::loadJson(const char *payload) {
  doc.clear();
  DeserializationError err = deserializeJson(doc, payload);
  if (err) {
    DBGLN("Could not deserialize payload: %s", err.c_str());
    return SM_ERROR;
  }
  root = doc.as<JsonVariant>();
  return SM_SUCCESS;
}

/**
   Open file
*/
void SettingsManager::openSPIFFS() {
  if (!SPIFFS.begin()) {
    delay(100);
    DBGLN("Could not mount SPIFFS file system");
  } else {
    DBGLN("SPIFFS file system, open");
  }
}

/**
   Returns the JsonVariant of a given key
*/
JsonVariant SettingsManager::getJsonVariant(const char *key, bool addIfMissing) {
  DBGLN("-> Searching for key: %s", key);
  //Maybe i'm lucky ...
  JsonVariant val = root.getMember(key);
  if (!val.isNull()) {
    DBGLN("Key found in root: %s", key);
    return val;
  }
  char _key[100] = {0};
  strcpy(_key, key);
  char *k = strchr(_key, '.');

  //if it does not have any . then is not existing
  if (k == nullptr) {
    if (addIfMissing) {
      DBGLN("Adding not existing key: %s", key);
      return root.getOrAddMember(key);
    } else {
      DBGLN("Key not found %s", key);
      return JsonVariant();
    }
  }

  //for sure it has at least one .
  char *crs = &_key[0];
  JsonVariant node = root;
  while (k != nullptr) {
    //replace the . with \0 to split the string
    k[0] = '\0';
    if (strlen(crs) > 0) {
      if (!node.getMember(crs).isNull()) {
        node = node.getMember(crs);
      } else if (!addIfMissing) {
        DBGLN("Key not found: %s", crs);
        return JsonVariant();
      } else {
        DBGLN("Adding not existing key: %s", crs);
        node = node.getOrAddMember(crs);
      }
    }
    k++;
    crs = k;
    k = strchr(crs, '.');
    if (k == nullptr) {
      if (node.getMember(crs).isNull() && addIfMissing) {
        DBGLN("Adding not existing key: %s", crs);
        node = node.getOrAddMember(crs);
      } else {
        node = node.getMember(crs);
      }
      break;
    }
  }
  return node;
};

/**
   Returns the JsonObject stored to a specific key
*/
JsonObject SettingsManager::getJsonObject(const char *key, bool addIfMissing) {
  JsonVariant item = getJsonVariant(key, addIfMissing);
  if (!item.isNull()) {
    return item.as<JsonObject>();
  } else if (addIfMissing) {
    return item.getOrAddMember(key);
  } else {
    return JsonObject();
  }
}

/**
   Returns the JsonArray stored to a specific key
*/
JsonArray SettingsManager::getJsonArray(const char *key, bool addIfMissing) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<JsonArray>();
  } else if (addIfMissing) {
    return item.getOrAddMember(key);
  } else {
    return JsonArray();
  }
}

signed int SettingsManager::getInt(const char *key, const signed int defaultValue) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<signed int>();
  } else {
    return defaultValue;
  }
}

unsigned int SettingsManager::getUInt(const char *key, const unsigned int defaultValue) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<unsigned int>();
  } else {
    return defaultValue;
  }
}

signed short SettingsManager::getShort(const char *key, const signed short defaultValue) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<signed short>();
  } else {
    return defaultValue;
  }
}

unsigned short SettingsManager::getUShort(const char *key, const unsigned short defaultValue) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<unsigned short>();
  } else {
    return defaultValue;
  }
}

signed long SettingsManager::getLong(const char *key, const signed long defaultValue) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<signed long>();
  } else {
    return defaultValue;
  }
}

unsigned long SettingsManager::getULong(const char *key, const unsigned long defaultValue) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<unsigned long>();
  } else {
    return defaultValue;
  }
}

char SettingsManager::getCChar(const char *key, const char defaultValue) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    const char *x = item.as<const char *>();
    return x[0];
  } else {
    return defaultValue;
  }
}

signed char SettingsManager::getSChar(const char *key, const signed char defaultValue) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<signed char>();
  } else {
    return defaultValue;
  }
}

unsigned char SettingsManager::getUChar(const char *key, const unsigned char defaultValue) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<unsigned char>();
  } else {
    return defaultValue;
  }
}

const char *SettingsManager::getChar(const char *key, const char *defaultValue) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<char *>();
  } else {
    return defaultValue;
  }
}

String SettingsManager::getString(const char *key, const String defaultValue) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<String>();
  } else {
    return defaultValue;
  }
}

float SettingsManager::getFloat(const char *key, const float defaultValue) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<float>();
  } else {
    return defaultValue;
  }
}

double SettingsManager::getDouble(const char *key, const double defaultValue) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<double>();
  } else {
    return defaultValue;
  }
}

bool SettingsManager::getBool(const char *key, const bool defaultValue) {
  JsonVariant item = getJsonVariant(key);
  if (!item.isNull()) {
    return item.as<bool>();
  } else {
    return defaultValue;
  }
}

int SettingsManager::setInt(const char *key, const signed int value, bool addIfMissing) {
  JsonVariant item = getJsonVariant(key, addIfMissing);
  if (addIfMissing || !item.isNull()) {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  } else {
    DBGLN("null node");
    return SM_KEY_NOT_FOUND;
  }
}

int SettingsManager::setShort(const char *key, const signed short value, bool addIfMissing) {
  JsonVariant item = getJsonVariant(key, addIfMissing);
  if (addIfMissing || !item.isNull()) {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  } else {
    DBGLN("null node");
    return SM_KEY_NOT_FOUND;
  }
}

int SettingsManager::setLong(const char *key, const signed long value, bool addIfMissing) {
  JsonVariant item = getJsonVariant(key, addIfMissing);
  if (addIfMissing || !item.isNull()) {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  } else {
    DBGLN("null node");
    return SM_KEY_NOT_FOUND;
  }
}

int SettingsManager::setCChar(const char *key, const char value, bool addIfMissing) {
  JsonVariant item = getJsonVariant(key, addIfMissing);
  if (addIfMissing || !item.isNull()) {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  } else {
    DBGLN("null node");
    return SM_KEY_NOT_FOUND;
  }
}

int SettingsManager::setChar(const char *key, const char *value, bool addIfMissing) {
  JsonVariant item = getJsonVariant(key, addIfMissing);
  if (addIfMissing || !item.isNull()) {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  } else {
    DBGLN("null node");
    return SM_KEY_NOT_FOUND;
  }
}

int SettingsManager::setString(const char *key, const String value, bool addIfMissing) {
  JsonVariant item = getJsonVariant(key, addIfMissing);
  if (addIfMissing || !item.isNull()) {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  } else {
    DBGLN("null node");
    return SM_KEY_NOT_FOUND;
  }
}

int SettingsManager::setFloat(const char *key, const float value, bool addIfMissing) {
  JsonVariant item = getJsonVariant(key, addIfMissing);
  if (addIfMissing || !item.isNull()) {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  } else {
    DBGLN("null node");
    return SM_KEY_NOT_FOUND;
  }
}

int SettingsManager::setDouble(const char *key, const double value, bool addIfMissing) {
  JsonVariant item = getJsonVariant(key, addIfMissing);
  if (addIfMissing || !item.isNull()) {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  } else {
    DBGLN("null node");
    return SM_KEY_NOT_FOUND;
  }
}

int SettingsManager::setBool(const char *key, const bool value, bool addIfMissing) {
  JsonVariant item = getJsonVariant(key, addIfMissing);
  if (addIfMissing || !item.isNull()) {
    return item.set(value) ? SM_SUCCESS : SM_ERROR;
  } else {
    DBGLN("null node");
    return SM_KEY_NOT_FOUND;
  }
}
