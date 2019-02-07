#ifndef _MESSAGE_HANDER_H_
#define _MESSAGE_HANDER_H_
#include <SerialReceiver.h>
#include "DictPrinter.h"
#include "constants.h"
#include "SavedVariables.h"

class MessageHandler : public SerialReceiver {

 public:
  void processMsg();

 private:
  DictPrinter dprint;
  void msgSwitchYard();
  void handleGetDevInfo();
  void handleGetCmds();

  bool checkNumberOfArgs(int num);
  bool checkSerialNumberArg(int serial_number);
  void systemCmdRsp(bool flag);

  void handleGetRspCodes();
  void handleSetSerialNumber();

  bool checkValveArg(int valve);
  void handleSetOdorValveOn();
  void handleSetOdorValvesOff();
  void handleGetOdorValveOn();

  bool checkMfcArg(int mfc);
  bool checkPercentCapacityArg(int percent_capacity);
  void handleSetMfcFlowRate();
  void handleGetMfcFlowRateSetting();
  void handleGetMfcFlowRateMeasure();
  void handleGetMfcSerialNumber();
  void handleGetMfcCapacity();
  void handleGetMfcCapacityUnits();
  void handleGetMfcFluidName();

  void handleSetValve0NormallyOpened();
  void handleSetValve0NormallyClosed();

  // Development
  void handleDebug();
};

extern MessageHandler messageHandler;
#endif
