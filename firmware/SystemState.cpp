#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "string.h"
#include "SystemState.h"

SystemState::SystemState() {
  setErrMsg("");
}

void SystemState::setErrMsg(char *msg) {
  strncpy(errMsg,msg,SYS_ERR_BUF_SZ);
}

void SystemState::initialize() {
  valveDriver = TLE7232G(constants::valveDriverCsPin,constants::valveDriverInPin);

  for (int mfcIndex=0; mfcIndex<constants::mfcCount; mfcIndex++) {
    mfc[mfcIndex] = Bronkhorst(mfcIndex+1);
    mfc[mfcIndex].init();
  }

  // Initialize SPI:
  SPI.setDataMode(SPI_MODE1);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  SPI.setBitOrder(MSBFIRST);
  SPI.begin();

  valveDriver.init();
  setOdorValveOn(0);
}

bool SystemState::setOdorValveOn(int valve) {
  uint32_t channels = 0b11;

  if ((valve == 0) && (savedVariables.getValve0NormallyOpen())){
    channels = 0;
  } else if (savedVariables.getValve0NormallyOpen()) {
    channels |= channels << (2*valve);
  } else {
    channels = channels << (2*valve);
  }
  valveDriver.setChannels(channels);
  this->valve = valve;
  return true;
}

bool SystemState::setOdorValvesOff() {
  uint32_t channels = 0;
  if (savedVariables.getValve0NormallyOpen()) {
    channels = 0b11;
  }
  valveDriver.setChannels(channels);
  this->valve = -1;
  return true;
}

int SystemState::getOdorValveOn() {
  return valve;
}

bool SystemState::setMfcFlowRate(int mfcIndex, int percent_capacity) {
  int setpoint = map(percent_capacity,constants::percentCapacityMin,constants::percentCapacityMax,constants::setpointMin,constants::setpointMax);
  return mfc[mfcIndex].setSetpoint(setpoint);
}

bool SystemState::getMfcFlowRateSetting(int mfcIndex, int &percent_capacity) {
  int setpoint = mfc[mfcIndex].getSetpoint();
  percent_capacity = map(setpoint,constants::setpointMin,constants::setpointMax,constants::percentCapacityMin,constants::percentCapacityMax);
  return true;
}

bool SystemState::getMfcFlowRateMeasure(int mfcIndex, int &percent_capacity) {
  int measure = mfc[mfcIndex].getMeasure();
  percent_capacity = map(measure,constants::setpointMin,constants::setpointMax,constants::percentCapacityMin,constants::percentCapacityMax);
  return true;
}

bool SystemState::getMfcSerialNumber(int mfcIndex, String &serial_number) {
  return mfc[mfcIndex].getSerialNumber(serial_number);
}

bool SystemState::getMfcCapacity(int mfcIndex, int &capacity) {
  capacity = (int)mfc[mfcIndex].getCapacity();
  return true;
}

bool SystemState::getMfcCapacityUnits(int mfcIndex, String &capacity_units) {
  return mfc[mfcIndex].getCapacityUnits(capacity_units);
}

bool SystemState::getMfcFluidName(int mfcIndex, String &fluid_name) {
  return mfc[mfcIndex].getFluidName(fluid_name);
}


SystemState systemState;


