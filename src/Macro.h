//=================[ DEBUGGER ]================
#  ifdef DEBUG_SETTINGS
#    define DBG(x) debug->print(x)
#    define DBGLN(x) debug->println(x)
#  else
#    define DBG(X)
#    define DBGLN(X)
#  endif // DEBUG


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
