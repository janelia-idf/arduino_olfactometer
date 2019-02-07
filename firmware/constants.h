#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

namespace constants {
  enum {valveCount=16};
  enum {mfcCount=2};

  // Communications parameters
  extern const int baudrate;

  // Device parameters
  extern const int modelNumber;
  extern const int serialNumberMin;
  extern const int serialNumberMax;
  extern const int firmwareNumber;

  // Pin assignment
  extern const int valveDriverCsPin;
  extern const int valveDriverInPin;

  // Valve parameters
  extern const bool valve0NormallyOpenDefault;

  // Mfc parameters
  extern const int percentCapacityMin;
  extern const int percentCapacityMax;
  extern const int setpointMin;
  extern const int setpointMax;
}
#endif
