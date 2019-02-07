#include "constants.h"
namespace constants {
  // Communications parameters
  const int baudrate = 9600;

  // Device parameters
  const int modelNumber = 384;
  const int serialNumberMin = 0;
  const int serialNumberMax = 255;
  const int firmwareNumber = 4;

  // Pin assignment
  const int valveDriverCsPin = 49;
  const int valveDriverInPin = 48;

  // valve parameters
  const bool valve0NormallyOpenDefault = true;

  // Mfc parameters
  const int percentCapacityMin = 0;
  const int percentCapacityMax = 100;
  const int setpointMin = 0;
  const int setpointMax = 32000;
}
