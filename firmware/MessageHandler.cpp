#include <util/atomic.h>
#include "MessageHandler.h"
#include "Streaming.h"
#include "SystemState.h"

enum {
  cmdGetDevInfo,                    // Done
  cmdGetCmds,                       // Done
  cmdGetRspCodes,                   // Done
  cmdSetSerialNumber,               //

  cmdSetOdorValveOn,                //
  cmdSetOdorValvesOff,              //
  cmdGetOdorValveOn,                //

  cmdSetMfcFlowRate,                //
  cmdGetMfcFlowRateSetting,         //
  cmdGetMfcFlowRateMeasure,         //
  cmdGetMfcSerialNumber,            //
  cmdGetMfcCapacity,                //
  cmdGetMfcCapacityUnits,           //
  cmdGetMfcFluidName,               //

  cmdSetValve0NormallyOpened,       //
  cmdSetValve0NormallyClosed,       //

  // DEVELOPMENT
  cmdDebug,
};


const int rspSuccess = 1;
const int rspError = 0;

void MessageHandler::processMsg() {
  while (Serial.available() > 0) {
    process(Serial.read());
    if (messageReady()) {
      msgSwitchYard();
      reset();
    }
  }
  return;
}

void MessageHandler::msgSwitchYard() {
  int cmd = readInt(0);
  dprint.start();
  dprint.addIntItem("cmd_id", cmd);

  switch (cmd) {

  case cmdGetDevInfo:
    handleGetDevInfo();
    break;

  case cmdGetCmds:
    handleGetCmds();
    break;

  case cmdGetRspCodes:
    handleGetRspCodes();
    break;

  case cmdSetSerialNumber:
    handleSetSerialNumber();
    break;

  case cmdSetOdorValveOn:
    handleSetOdorValveOn();
    break;

  case cmdSetOdorValvesOff:
    handleSetOdorValvesOff();
    break;

  case cmdGetOdorValveOn:
    handleGetOdorValveOn();
    break;

  case cmdSetMfcFlowRate:
    handleSetMfcFlowRate();
    break;

  case cmdGetMfcFlowRateSetting:
    handleGetMfcFlowRateSetting();
    break;

  case cmdGetMfcFlowRateMeasure:
    handleGetMfcFlowRateMeasure();
    break;

  case cmdGetMfcSerialNumber:
    handleGetMfcSerialNumber();
    break;

  case cmdGetMfcCapacity:
    handleGetMfcCapacity();
    break;

  case cmdGetMfcCapacityUnits:
    handleGetMfcCapacityUnits();
    break;

  case cmdGetMfcFluidName:
    handleGetMfcFluidName();
    break;

  case cmdSetValve0NormallyOpened:
    handleSetValve0NormallyOpened();
    break;

  case cmdSetValve0NormallyClosed:
    handleSetValve0NormallyClosed();
    break;

  // DEVELOPMENT
  case cmdDebug:
    handleDebug();
    break;

  default:
    dprint.addIntItem("status", rspError);
    dprint.addStrItem("err_msg", "unknown command");
    break;
  }
  dprint.stop();
}

void MessageHandler::handleGetCmds() {
  dprint.addIntItem("status", rspSuccess);
  dprint.addIntItem("getDevInfo", cmdGetDevInfo);
  dprint.addIntItem("getCmds", cmdGetCmds);
  dprint.addIntItem("getRspCodes", cmdGetRspCodes);
  dprint.addIntItem("setArduinoSerialNumber", cmdSetSerialNumber);

  dprint.addIntItem("setOdorValveOn", cmdSetOdorValveOn);
  dprint.addIntItem("setOdorValvesOff", cmdSetOdorValvesOff);
  dprint.addIntItem("getOdorValveOn", cmdGetOdorValveOn);

  dprint.addIntItem("setMfcFlowRate", cmdSetMfcFlowRate);
  dprint.addIntItem("getMfcFlowRateSetting", cmdGetMfcFlowRateSetting);
  dprint.addIntItem("getMfcFlowRateMeasure", cmdGetMfcFlowRateMeasure);
  dprint.addIntItem("getMfcSerialNumber", cmdGetMfcSerialNumber);
  dprint.addIntItem("getMfcCapacity", cmdGetMfcCapacity);
  dprint.addIntItem("getMfcCapacityUnits", cmdGetMfcCapacityUnits);
  dprint.addIntItem("getMfcFluidName", cmdGetMfcFluidName);

  dprint.addIntItem("setValve0NormallyOpened", cmdSetValve0NormallyOpened);
  dprint.addIntItem("setValve0NormallyClosed", cmdSetValve0NormallyClosed);

  // DEVELOPMENT
  dprint.addIntItem("cmdDebug", cmdDebug);
}

void MessageHandler::handleGetDevInfo() {
  dprint.addIntItem("status", rspSuccess);
  dprint.addIntItem("model_number",  constants::modelNumber);
  dprint.addIntItem("serial_number", savedVariables.getSerialNumber());
  dprint.addIntItem("firmware_number", constants::firmwareNumber);
  dprint.addIntItem("valve_count",  constants::valveCount);
  dprint.addIntItem("mfc_count",  constants::mfcCount);
  dprint.addIntItem("valve_0_normally_open",  savedVariables.getValve0NormallyOpen());
}

bool MessageHandler::checkNumberOfArgs(int num) {
  bool flag = true;
  if (numberOfItems() != num) {
    dprint.addIntItem("status", rspError);
    dprint.addStrItem("err_msg", "incorrect number of arguments");
    flag = false;
  }
  return flag;
}

bool MessageHandler::checkSerialNumberArg(int serial_number) {
  bool flag = true;
  if ((serial_number<constants::serialNumberMin) || (constants::serialNumberMax<serial_number)) {
    dprint.addIntItem("status", rspError);
    dprint.addStrItem("err_msg", "serial number argument out of range");
    flag = false;
  }
  return flag;
}

void MessageHandler::systemCmdRsp(bool flag) {
  if (flag) {
    dprint.addIntItem("status", rspSuccess);
  }
  else {
    dprint.addIntItem("status", rspError);
    dprint.addStrItem("err_msg", systemState.errMsg);
  }
}

void MessageHandler::handleGetRspCodes() {
  dprint.addIntItem("status", rspSuccess);
  dprint.addIntItem("rsp_success",rspSuccess);
  dprint.addIntItem("rsp_error", rspError);
}

void MessageHandler::handleSetSerialNumber() {
  if (!checkNumberOfArgs(2)) {return;}
  int serialNumber = readInt(1);
  if (checkSerialNumberArg(serialNumber)) {
    systemCmdRsp(savedVariables.setSerialNumber(serialNumber));
  }
}

bool MessageHandler::checkValveArg(int valve) {
  bool flag = true;
  if ((valve<0) || (constants::valveCount<=valve)) {
    dprint.addIntItem("status", rspError);
    dprint.addStrItem("err_msg", "valve argument out of range");
    flag = false;
  }
  return flag;
}

void MessageHandler::handleSetOdorValveOn() {
  if (!checkNumberOfArgs(2)) {return;}
  int valve = readInt(1);
  if (checkValveArg(valve)) {
    systemCmdRsp(systemState.setOdorValveOn(valve));
  }
}

void MessageHandler::handleSetOdorValvesOff() {
  systemCmdRsp(systemState.setOdorValvesOff());
}

void MessageHandler::handleGetOdorValveOn() {
  dprint.addIntItem("status", rspSuccess);
  dprint.addIntItem("valve", systemState.getOdorValveOn());
}

bool MessageHandler::checkMfcArg(int mfc) {
  bool flag = true;
  if ((mfc<0) || (constants::mfcCount<=mfc)) {
    dprint.addIntItem("status", rspError);
    dprint.addStrItem("err_msg", "mfc argument out of range");
    flag = false;
  }
  return flag;
}

bool MessageHandler::checkPercentCapacityArg(int percent_capacity) {
  bool flag = true;
  if ((percent_capacity<constants::percentCapacityMin) || (constants::percentCapacityMax<percent_capacity)) {
    dprint.addIntItem("status", rspError);
    dprint.addStrItem("err_msg", "percent_capacity argument out of range");
    flag = false;
  }
  return flag;
}

void MessageHandler::handleSetMfcFlowRate() {
  if (!checkNumberOfArgs(3)) {return;}
  int mfc = readInt(1);
  int percent_capacity = readInt(2);
  if (checkMfcArg(mfc) && checkPercentCapacityArg(percent_capacity)) {
    systemCmdRsp(systemState.setMfcFlowRate(mfc,percent_capacity));
  }
}

void MessageHandler::handleGetMfcFlowRateSetting() {
  if (!checkNumberOfArgs(2)) {return;}
  int mfc = readInt(1);
  if (checkMfcArg(mfc)) {
    int percent_capacity;
    if (systemState.getMfcFlowRateSetting(mfc,percent_capacity)) {
      dprint.addIntItem("status", rspSuccess);
      dprint.addIntItem("percent_capacity", percent_capacity);
    } else {
      dprint.addIntItem("status", rspError);
      dprint.addStrItem("err_msg", "unable to get mfc flow rate setting");
    }
  }
}

void MessageHandler::handleGetMfcFlowRateMeasure() {
  if (!checkNumberOfArgs(2)) {return;}
  int mfc = readInt(1);
  if (checkMfcArg(mfc)) {
    int percent_capacity;
    if (systemState.getMfcFlowRateMeasure(mfc,percent_capacity)) {
      dprint.addIntItem("status", rspSuccess);
      dprint.addIntItem("percent_capacity", percent_capacity);
    } else {
      dprint.addIntItem("status", rspError);
      dprint.addStrItem("err_msg", "unable to get mfc flow rate measure");
    }
  }
}

void MessageHandler::handleGetMfcSerialNumber() {
  if (!checkNumberOfArgs(2)) {return;}
  int mfc = readInt(1);
  if (checkMfcArg(mfc)) {
    String mfc_serial_number;
    if (systemState.getMfcSerialNumber(mfc,mfc_serial_number)) {
      dprint.addIntItem("status", rspSuccess);
      dprint.addStrItem("mfc_serial_number", mfc_serial_number);
    } else {
      dprint.addIntItem("status", rspError);
      dprint.addStrItem("err_msg", "unable to get mfc serial number");
    }
  }
}

void MessageHandler::handleGetMfcCapacity() {
  if (!checkNumberOfArgs(2)) {return;}
  int mfc = readInt(1);
  if (checkMfcArg(mfc)) {
    int capacity;
    if (systemState.getMfcCapacity(mfc,capacity)) {
      dprint.addIntItem("status", rspSuccess);
      dprint.addIntItem("capacity", capacity);
    } else {
      dprint.addIntItem("status", rspError);
      dprint.addStrItem("err_msg", "unable to get mfc capacity");
    }
  }
}

void MessageHandler::handleGetMfcCapacityUnits() {
  if (!checkNumberOfArgs(2)) {return;}
  int mfc = readInt(1);
  if (checkMfcArg(mfc)) {
    String capacity_units;
    if (systemState.getMfcCapacityUnits(mfc,capacity_units)) {
      dprint.addIntItem("status", rspSuccess);
      dprint.addStrItem("capacity_units", capacity_units);
    } else {
      dprint.addIntItem("status", rspError);
      dprint.addStrItem("err_msg", "unable to get mfc capacity units");
    }
  }
}

void MessageHandler::handleGetMfcFluidName() {
  if (!checkNumberOfArgs(2)) {return;}
  int mfc = readInt(1);
  if (checkMfcArg(mfc)) {
    String fluid_name;
    if (systemState.getMfcFluidName(mfc,fluid_name)) {
      dprint.addIntItem("status", rspSuccess);
      dprint.addStrItem("fluid_name", fluid_name);
    } else {
      dprint.addIntItem("status", rspError);
      dprint.addStrItem("err_msg", "unable to get mfc fluid name");
    }
  }
}

void MessageHandler::handleSetValve0NormallyOpened() {
  systemCmdRsp(savedVariables.setValve0NormallyOpen(true));
}

void MessageHandler::handleSetValve0NormallyClosed() {
  systemCmdRsp(savedVariables.setValve0NormallyOpen(false));
}

// -------------------------------------------------


void MessageHandler::handleDebug() {
  char name[20];
  dprint.addIntItem("status", rspSuccess);
}


MessageHandler messageHandler;
