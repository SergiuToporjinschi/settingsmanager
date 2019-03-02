#ifndef Macros_h
#define Macros_h

#include <Arduino.h>

#define DEBUGER
#define DEBUGER_MEM
#define SERIAL_BAUDRATE         9600



#ifdef DEBUGER

#define DBGF(x, ...) do {\
    char all[200] = "DBG-->";\
    strcat(all,x);\
    strcat(all,"<--DBG");\
    char buff[201]={0};\
    snprintf(buff, 200, all, __VA_ARGS__);\
    Serial.print(buff); \
    Serial.println(); \
  } while (0)

#define DBGBUF(buf, cnt) do{ \
    for (int i = 0; i < cnt; i++) {\
      Serial.print(buf[i], DEC); Serial.print(" ");\
    }\
  }while(0);

#define DBG(x) Serial.print(x)
//#define DBGLN(x) do {\
//    char all[500] = "DBG-->";\
//    strcat(all,x);\
//    strcat(all,"<--DBG");\
//    Serial.println(all);\
//  } while(0)
//#else
#define DBGLN(x) do {\
    Serial.println(x);\
  } while(0)
#else

#define DBGF(x, ...)
#define DBG(x)
#define DBGLN(x)
#endif


#ifdef DEBUGER_MEM
#ifdef ESP8266
#define DBGMEM DBGF("FreeHip/frag: %ubytes, %u%%; BiggestBlock: %ubytes; FreeStkCnt: %un;", ESP.getFreeHeap(), ESP.getHeapFragmentation(), ESP.getMaxFreeBlockSize(),ESP.getFreeContStack());
#else
#define DBGMEM 
#endif
#else 
#define DBGMEM
#endif




#endif
