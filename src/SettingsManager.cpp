#define DEBUG_PRINT(x) Serial.println(x)
#include "Arduino.h"
#include "SettingsManager.h"

void SettingsManager::readSettings(String fileName) {
  DEBUG_PRINT("Reading settings from: " + fileName);
  openSPIFFS();
  File file = SPIFFS.open(fileName, "r");
  if (!file) {
    delay(1000);
    DEBUG_PRINT("Could not open file");
    SPIFFS.end();
    return;
  } else {
    populateSettings(file);
  }
  DEBUG_PRINT("Closing file");
  file.close();
  SPIFFS.end();
};

void SettingsManager::writeSettings(const String &fileName) {
  String content = SettingsManager::stringify(settings);
  writeSettings(fileName, content);
};

void SettingsManager::writeSettings(const String &fileName, const String &content) {
  DEBUG_PRINT("Writing settings to: " + fileName);
  openSPIFFS();
  File file = SPIFFS.open(fileName, "w");
  if (!file) {
    delay(1000);
  } else {
    file.print("# written today\n");
    file.print(content);
  }
  DEBUG_PRINT("Closing file");
  file.close();
  SPIFFS.end();
};

void SettingsManager::openSPIFFS() {
  if (!SPIFFS.begin()) {
    delay(1000);
    DEBUG_PRINT("Could not mount SPIFFS file system");
  }
};

void SettingsManager::populateSettings(File &file) {
  DEBUG_PRINT("Populate settings");
  while (file.available()) {
    String line = file.readStringUntil('\n');
    line.trim();
    DEBUG_PRINT(line);
    if (line.length() != 0 && !line.startsWith("#")) {
      int index = line.indexOf("#");
      if (index > 0) {
        line = line.substring(0, index);
        line.trim();
      }
      setValues(line);
    }
  }
};

void SettingsManager::setValues(String &line) {
  int poz = line.indexOf("=");
  String key = line.substring(0, poz);
  String value = line.substring(poz + 1);
  key.trim();
  value.trim();
  settings[key] = value;
};

String SettingsManager::stringify(std::map <String, String> &settings) {
  String val = "";
  for (std::map<String, String>::iterator it = settings.begin(); it != settings.end(); ++it)
    val += it->first + "=" + it->second + '\n';
  return val;
};

std::map <String, String> SettingsManager::getSettings() {
  return settings;
};

const char *SettingsManager::getChar(String key) {
  return settings[key].c_str();
};

String SettingsManager::getString(String key) {
  return settings[key];
};

int SettingsManager::getInt(String key) {
  return settings[key].toInt();
};

bool SettingsManager::getBool(String key) {
  String value = settings[key];
  value.trim();
  value.toLowerCase();
  return value == "true";
};

long SettingsManager::getLong(String key){
  return atol(settings[key].c_str());
};

void SettingsManager::setString(String key, String value) {
  settings[key] = value;
};

void SettingsManager::setInt(String key, int value) {
  settings[key] = String(value);
};

void SettingsManager::setLong(String key, long value){
  settings[key] = String(value);
};

void SettingsManager::setBool(String key, bool value) {
  if (value) {
    settings[key] = "true";
  } else {
    settings[key] =  "false";
  }
};
