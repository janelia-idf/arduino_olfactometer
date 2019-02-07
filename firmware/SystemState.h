#ifndef _SYSTEM_STATE_H_
#define _SYSTEM_STATE_H_
#include <SPI.h>
#include <Tle7232g.h>
#include "Bronkhorst.h"
#include "constants.h"
#include "SavedVariables.h"

enum {SYS_ERR_BUF_SZ=50};

class SystemState {

 public:
  SystemState();

  void setErrMsg(char *);
  char errMsg[SYS_ERR_BUF_SZ];

  void initialize();

  bool setOdorValveOn(int valve);
  bool setOdorValvesOff();
  int getOdorValveOn();

  bool setMfcFlowRate(int mfcIndex, int percent_capacity);
  bool getMfcFlowRateSetting(int mfcIndex, int &percent_capacity);
  bool getMfcFlowRateMeasure(int mfcIndex, int &percent_capacity);
  bool getMfcSerialNumber(int mfcIndex, String &serial_number);
  bool getMfcCapacity(int mfcIndex, int &capacity);
  bool getMfcCapacityUnits(int mfcIndex, String &capacity_units);
  bool getMfcFluidName(int mfcIndex, String &fluid_name);

 private:
  int valve;
  TLE7232G valveDriver;
  Bronkhorst mfc[constants::mfcCount];
};

extern SystemState systemState;

#endif
