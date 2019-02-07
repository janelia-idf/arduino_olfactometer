#include "SavedVariables.h"

SavedVariables::SavedVariables()
{
  initialize();
};

void SavedVariables::initialize() {
  // Check to see if EEPROM values have been initialized for the very first time, if not, initialize
  if (EEPROM.read(eepromAddressInitialized) != initializedValue) {
    EEPROM.write(eepromAddressInitialized,initializedValue);
    EEPROM.write(eepromAddressSerialNumber,constants::serialNumberMin);
    EEPROM.write(eepromAddressValve0NormallyOpen,int(constants::valve0NormallyOpenDefault));
  }

  this->_serialNumber = EEPROM.read(eepromAddressSerialNumber);
  this->_valve0NormallyOpen = bool(EEPROM.read(eepromAddressValve0NormallyOpen));
}

int SavedVariables::getSerialNumber() {
  return _serialNumber;
}

bool SavedVariables::setSerialNumber(int serial_number) {
  this->_serialNumber = serial_number;
  EEPROM.write(eepromAddressSerialNumber,serial_number);
  return true;
}

bool SavedVariables::getValve0NormallyOpen() {
  return _valve0NormallyOpen;
}

bool SavedVariables::setValve0NormallyOpen(bool normally_open) {
  this->_valve0NormallyOpen = normally_open;
  EEPROM.write(eepromAddressValve0NormallyOpen,int(normally_open));
  return true;
}


SavedVariables savedVariables;
