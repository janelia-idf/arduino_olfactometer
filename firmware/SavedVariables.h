// SavedVariables.h
#ifndef SavedVariables_h
#define SavedVariables_h

#include <stdlib.h>
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif
#include <EEPROM.h>
#include "constants.h"


class SavedVariables {

 public:

  SavedVariables();
  int getSerialNumber();
  bool setSerialNumber(int serial_number);

  bool getValve0NormallyOpen();
  bool setValve0NormallyOpen(bool normally_open);

 private:

  enum {eepromAddressInitialized,
        eepromAddressSerialNumber,
        eepromAddressValve0NormallyOpen
  };

  enum {initializedValue = 12};

  int _serialNumber;
  bool _valve0NormallyOpen;

  void initialize();

};

extern SavedVariables savedVariables;

#endif
