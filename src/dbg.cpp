#include "dbg.h"

#ifdef DEBUG
namespace dbg {
#  if defined(DEBUG_RX)
#    if DEBUG_RX >= 0
  SoftwareSerial *debug = new SoftwareSerial(DEBUG_RX, DEBUG_TX);
#    endif
#  else
  HardwareSerial *debug = &Serial;
#  endif

  void initDebug() {
    debug->begin(DEBUG_SPD);
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
#endif