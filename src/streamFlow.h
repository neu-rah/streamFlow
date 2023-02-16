#pragma once
#define RSITE_STREAM_FLOW

#include <Arduino.h>

namespace StreamFlow {

  using Serial_=decltype(Serial);

  /// @brief currect output decimal places
  extern byte m_prec;
  /// @brief currect output digit base to use on integral print
  extern byte m_radix;

  /// @brief use _radix stream external info to request Arduino radix format
  /// @tparam T numeric integral type
  /// @param s output object
  /// @param n numeric integral data
  /// @return the output object
  template<typename T> Serial_& _print_integral_num(Serial_& s,T n) {s.print(n,m_radix);m_radix=DEC;return s;}
  template<typename T> Serial_& _print_scientific_num(Serial_& s,T n) {s.print(n,m_prec);return s;}

  /// @brief hold desired precision till next data in printedm then restores the previous precision
  struct Precision {
    byte np;
    Precision(int p):np(p) {}
    /// @brief hold precision and stream while waitibg for next data
    struct Bound {
      Serial_& s;
      byte np;
      Bound(Serial_& s,int p):s(s),np(p) {}
      /// @brief print the next data and return to old precision format
      /// @tparam T data type
      /// @param o data
      /// @return the stream to resume printing
      template<typename T>
      Serial_& operator<<(const T o) {
        byte tmp=m_prec;
        m_prec=np;
        s<<o;
        m_prec=tmp;
        return s;
      }
    };
    Bound operator<<(Serial_& s) {return Bound(s,np);}
  };

  /// @brief helps holding fotmat informtation external to stream
  /// @param p decimal places
  /// @return Precision 
  inline Precision precision(byte p) {return Precision(p);}

  /// @brief operator<< overload for native common types thru Serial_&
  /// @param s the output device
  /// @param o the data
  /// @return the output device
  /// @{
  inline Serial_& operator<<(Serial_& s,const __FlashStringHelper *o) {s.print(o);return s;} 
  inline Serial_& operator<<(Serial_& s,const unsigned long n) {return _print_integral_num(s,n);} 
  inline Serial_& operator<<(Serial_& s,const long n) {return _print_integral_num(s,n);} 
  inline Serial_& operator<<(Serial_& s,const unsigned int n) {return _print_integral_num(s,n);} 
  inline Serial_& operator<<(Serial_& s,const int n) {return _print_integral_num(s,n);} 
  inline Serial_& operator<<(Serial_& s,const float n) {return _print_scientific_num(s,n);} 
  inline Serial_& operator<<(Serial_& s,const double n) {return _print_scientific_num(s,n);} 
  inline Serial_& operator<<(Serial_& s,const String &str) {s.print(str);return s;} 
  inline Serial_& operator<<(Serial_& s,const char str[]) {s.print(str);return s;} 
  inline Serial_& operator<<(Serial_& s,const char c) {s.write(c);return s;} 
  inline Serial_& operator<<(Serial_& s,const Printable& x) {x.printTo(s);return s;}
  inline Serial_& operator<<(Serial_& s,Serial_&(f)(Serial_&)) {return f(s);}
  inline Precision operator<<(Serial_& s,Precision(p)(Serial_&)) {return p(s);}
  inline Precision::Bound operator<<(Serial_& s,Precision p) {return p.operator<<(s);}
  /// @}

  /// @brief stream modifyers
  /// @param s the output device
  /// @return the output device
  /// @{
  inline Serial_& endl(Serial_ &s) {s.println();s.flush();return s;}
  inline Serial_& flush(Serial_& s) {s.flush();return s;}
  inline Serial_& dec(Serial_& s) {m_radix=DEC;return s;}
  inline Serial_& hex(Serial_& s) {m_radix=HEX;return s;}
  inline Serial_& oct(Serial_& s) {m_radix=OCT;return s;}
  inline Serial_& bin(Serial_& s) {m_radix=BIN;return s;}
  /// @}

};/// namespace StreamFlow
