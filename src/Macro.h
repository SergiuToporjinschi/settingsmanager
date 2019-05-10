//=================[ DEBUGER ]=================
#ifndef DEBUGGER
#  define DEBUG_BEGIN
#  define DBGLN(x)
#  define DBG(x)
#else
#  define DEBUG_BEGIN Serial.begin(x)
#  define DBGLN(x) Serial.println(x)
#  define DBG(x) Serial.print(x)
#endif

//=================[ REVISION ]================
#ifndef REV
#  define REV (char *)"NONE"
#endif

//=================[ VERSION ]=================
#ifndef VER
#  define VER (char *)"0.0.0"
#endif

//==================[ CONFIG ]=================
#define JSON_LEN 1500
#define SM_KEY_NOT_FOUND 1
#define SM_ERROR -1
#define SM_SUCCESS 0
