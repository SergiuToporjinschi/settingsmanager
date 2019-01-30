#ifndef SettingsManager_h
#define SettingsManager_h
#include <ArduinoJson.h>
#include "Arduino.h"
#include <map>

#include "FS.h"

class SettingsManager {
  public:
    SettingsManager() {};
    void readSettings(String fileName);
    std::map <String, String> getSettings();
    void writeSettings(const String &fileName);
    void writeSettings(const String &fileName, const String &content);
    String getString(String key, String defaultValue = "");
    const char* getChar(String key, char* defaultValue = '\0');
    const char getChar(String key, char defaultValue = ' ');
    int getInt(String key, int defaultValue = 0);
    long getLong(String key, long defaultValue = 0);
    float getFloat(String key, float defaultValue = 0);
    double getDouble(String key, double defaultValue = 0);
    bool getBool(String key, bool defaultValue = 0);
    JsonVariant getVariant(String key);
    JsonObject& getJsonObject(String key);
    JsonArray& getJsonArray(String key);
    void populateSettings(File &file);
  private:
    JsonObject* root;
    String getFileContent(File &file);
    JsonObject* createJson(const char* payload);
    void openSPIFFS();
};
#endif
