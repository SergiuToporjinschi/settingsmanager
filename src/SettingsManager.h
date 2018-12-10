#ifndef SettingsManager_h
#define SettingsManager_h

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
    static String stringify(std::map <String, String> &settings);

    String getString(String key);
    const char *getChar(String key);
    int getInt(String key);
    long getLong(String key);
    bool getBool(String key);
    void setString(String key, String value);
    void setInt(String key, int value);
    void setLong(String key, long value);
    void setBool(String key, bool value);
  private:
    std::map <String, String> settings;
    void setValues(String &line);
    void populateSettings(File &file);
    void openSPIFFS();
};
#endif
