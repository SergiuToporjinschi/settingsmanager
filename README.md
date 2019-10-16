[![GitHub repo size in bytes](https://img.shields.io/github/repo-size/badges/shields.svg)](https://github.com/SergiuToporjinschi/settingsmanager)
[![GitHub last commit](https://img.shields.io/github/last-commit/SergiuToporjinschi/settingsmanager.svg)](https://github.com/SergiuToporjinschi/settingsmanager/commits/master)
[![GitHub stars](https://img.shields.io/github/stars/SergiuToporjinschi/settingsmanager.svg)](https://github.com/SergiuToporjinschi/settingsmanager/stargazers)
[![GitHub watchers](https://img.shields.io/github/watchers/SergiuToporjinschi/settingsmanager.svg)](https://github.com/SergiuToporjinschi/settingsmanager/watchers)
[![GitHub license](https://img.shields.io/github/license/SergiuToporjinschi/settingsmanager.svg)](https://github.com/SergiuToporjinschi/settingsmanager/blob/master/LICENSE)
[![Code Climate](https://codeclimate.com/github/codeclimate/codeclimate/badges/gpa.svg)](https://codeclimate.com/github/SergiuToporjinschi/settingsmanager)
[![Build Status](https://travis-ci.org/SergiuToporjinschi/settingsmanager.svg?branch=master)](https://travis-ci.org/SergiuToporjinschi/settingsmanager)

# Settings Manager

Intarface for reading, writing and managing settings in JSON format on SPIFFS.
# Dependency 
- [ArduinoJson V6](https://arduinojson.org/v6/api/jsonobject/)
# Compile macros

# Settings file
```json
{
 "esp" : {
	"delayTime": 300
 },
 "wlan": {
	"hostName": "hostName of esp",
	"ssid": "network sidd ",
	"password": "network password"
 },
 "mqtt": {
	"clientId": "mqttClientid",
	"server": "127.0.0.1",
	"port": "9999",
	"user": "mqttUser",
	"password": "mqttPassword",
	"status": {
		"topic": "topic/for/status"
	},
	"internalTopics" : {
		"settings": "Settings/topic",
		"cmd": "cmd/topic"
	}
 },
 "ledPin":13,
 "sketchVersion":"1.0",
 "updateServer":"http://testUpdateServer.com",
 "process": {
	"topic": "other/topic",
	"interval": 1000
 }
}
```

# Syntax
For getting value o a key you can call ``` sm.getInt(<path/key>[, defaultValue]) ``` The default value will be returned if the ```path/key``` has not been found.

For changing value of a key ``` sm.setInt(<path/key>, <value>) ``` will return SM_SUCCESS if the key has been found and changed; SM_KEY_NOT_FOUND if the key has not been found;

See [SettingsManager.h](https://github.com/SergiuToporjinschi/settingsmanager/blob/master/src/SettingsManager.h) for more information.

# Examples
Reading/loading settings from file;
```Cpp
#include "SettingsManager.h"

SettingsManager sm; //Initialize

void setup() {
    Serial.begin(115200);
    sm.readSettings("/config.json"); //Loading json from file config.json
}

void loop(){
    Serial.println("int ledPin: "); 
    Serial.print(sm.getInt("ledPin", 99)); //get the int value from json root
    Serial.println("Test getJsonVariant");
    
    JsonObject vr = sm.getJsonVariant("mqtt.status");
    if (!vr.isNull()) {
        serializeJsonPretty(vr, Serial);
        Serial.println("");
    } else {
        Serial.println("no variant");
    }
}
```

Loading json from a string
```Cpp
#include "SettingsManager.h"

SettingsManager sm; //Initialize

void setup() {
    Serial.begin(115200);
    sm.readSettings("/config.json"); //Loading json from file config.json
}

void loop(){
    sm.loadJson("{\"testInLoadingJson\":\"this is a string value\",\"Level1\":{\"Level2Key\":12,\"Level2Test\":true,\"Level3\":{\"float\":23.5}}}");
    JsonObject ob = sm.getRoot();
    if (!ob.isNull()) {
        serializeJsonPretty(ob, Serial);
        Serial.println("");
    } else {
        Serial.println("loadSetti: no ob");
    }
}
```

Change value of a key
```Cpp
#include "SettingsManager.h"

SettingsManager sm; //Initialize

void setup() {
    Serial.begin(115200);
    sm.readSettings("/config.json"); //Loading json from file config.json
}

void loop(){
    int res = sm.setString("updateServer", "Other Test");
    sm.setInt("ledPin", 15);
    sm.writeSettings("/config.json");
}
```
