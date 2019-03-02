#ifndef SettingsManager_h
#define SettingsManager_h
#include <ArduinoJson.h>
#include "Arduino.h"
#include "macros.h"
#include <map>

#include "FS.h"

class SettingsManager {
  public:
    SettingsManager() {};
    void readSettings(char * fileName);
    std::map <String, String> getSettings();
    void writeSettings(const char * fileName);
    //    void writeSettings(const String &fileName, const String &content);
    String getString(const char * key, const String defaultValue);
    signed int getInt(const char * key, const signed int defaultValue);
    signed short getShort(const char * key, const signed short defaultValue);
    signed long getLong(const char * key, const signed long defaultValue);
    unsigned long getLong(const char * key, const unsigned long defaultValue);
    signed char getChar(const char * key, const signed char defaultValue);
    const char * getChar(const char * key, const char * defaultValue);
    float getFloat(const char * key, const float defaultValue);
    double getDouble(const char * key, const double defaultValue);
    bool getBool(const char * key, const bool defaultValue);

    JsonVariant getJsonVariant(const char * key);
    JsonObject getJsonObject(const char * key);
    JsonArray getJsonArray(const char * key);

  private:
    DynamicJsonDocument doc = DynamicJsonDocument(1300);
    JsonObject root;
    String getFileContent(File &file);
    void createJson(const char* payload);
    void openSPIFFS();
};
#endif
