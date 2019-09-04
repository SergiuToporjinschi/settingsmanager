#include "dbg.h"

#if defined(DEBUG_CLASSIC) || defined(DEBUG_SOFT)
#  ifndef DEBUG_SOFT_RX
#    define DEBUG_SOFT_RX 3
#  endif
#  ifndef DEBUG_SOFT_TX
#    define DEBUG_SOFT_TX 1
#  endif
#  ifndef DEBUG_SOFT_SPD
#    define DEBUG_SOFT_SPD 115200
#  endif
#  ifndef DEBUG_CLASSIC_SPD
#    define DEBUG_CLASSIC_SPD 115200
#  endif
namespace dbg {

#  ifdef DEBUG_CLASSIC
  HardwareSerial *debug = &Serial;
  int32_t spd = DEBUG_CLASSIC_SPD;
#  elif DEBUG_SOFT
  SoftwareSerial *debug = new SoftwareSerial(DEBUG_SOFT_RX, DEBUG_SOFT_TX);
  int32_t spd = DEBUG_SOFT_SPD;
#  endif
  void initDebug() {
    debug->begin(spd);
  }

  void println(const String &s) {
    debug->println(s);
  }

  void println(const char c[]) {
    debug->println(c);
  }

  void println(char c) {
    debug->println(c);
  }

  void println(unsigned char b, int base) {
    debug->println(b, base);
  }

  void println(int num, int base) {
    debug->println(num, base);
  }

  void println(unsigned int num, int base) {
    debug->println(num, base);
  }

  void println(long num, int base) {
    debug->println(num, base);
  }

  void println(unsigned long num, int base) {
    debug->println(num, base);
  }

  void println(double num, int digits) {
    debug->println(num, digits);
  }

  void println(const Printable &x) {
    debug->println(x);
  }

  void printf(const char *format, ...) {
    va_list arg;
    debug->printf(format, arg);
  }

  void printf_P(PGM_P format, ...) {
    va_list arg;
    debug->printf(format, arg);
  }

  void print(const __FlashStringHelper *ifsh) {
    debug->print(ifsh);
  }

  void print(const String &s) {
    debug->print(s);
  }

  void print(const char str[]) {
    debug->print(str);
  }

  void print(char c) {
    debug->print(c);
  }

  void print(unsigned char b, int base) {
    debug->print(b, base);
  }

  void print(int n, int base) {
    debug->print(n, base);
  }

  void print(unsigned int n, int base) {
    debug->print(n, base);
  }

  void print(long n, int base) {
    debug->print(n, base);
  }

  void print(unsigned long n, int base) {
    debug->print(n, base);
  }

  void print(double n, int digits) {
    debug->print(n, digits);
  }

  void print(const Printable &x) {
    debug->print(x);
  }

} // namespace dbg
#else
namespace dbg {
  void setDebugImpl() {}
  void initDebug() {}
  void println(const String &s) {}
  void println(const char c[]) {}
  void println(char c) {}
  void println(unsigned char b, int base) {}
  void println(int num, int base) {}
  void println(unsigned int num, int base) {}
  void println(long num, int base) {}
  void println(unsigned long num, int base) {}
  void println(double num, int digits) {}
  void println(const Printable &x) {}
  void printf(const char *format, ...) {}
  void printf_P(PGM_P format, ...) {}
  void print(const __FlashStringHelper *ifsh) {}
  void print(const String &s) {}
  void print(const char str[]) {}
  void print(char c) {}
  void print(unsigned char b, int base) {}
  void print(int n, int base) {}
  void print(unsigned int n, int base) {}
  void print(long n, int base) {}
  void print(unsigned long n, int base) {}
  void print(double n, int digits) {}
  void print(const Printable &x) {}
} // namespace dbg
#endif