/*
 *  Copyright (c) 2019 Sinric. All rights reserved.
 *  Licensed under Creative Commons Attribution-Share Alike (CC BY-SA)
 *
 *  This file is part of the Sinric Pro (https://github.com/sinricpro/)
 */

#ifndef _SINRICTEMPERATURESENSOR_H_
#define _SINRICTEMPERATURESENSOR_H_

#include "SinricProDevice.h"

class SinricProTemperaturesensor :  public SinricProDevice {
  public:
	  SinricProTemperaturesensor(const char* deviceId, unsigned long eventWaitTime=60000);

    // event
    bool sendTemperatureEvent(float temperature, float humidity = -1, String cause = "PERIODIC_POLL");

  private:
};

SinricProTemperaturesensor::SinricProTemperaturesensor(const char* deviceId, unsigned long eventWaitTime) : SinricProDevice(deviceId, eventWaitTime) {}

bool SinricProTemperaturesensor::sendTemperatureEvent(float temperature, float humidity, String cause) {
  DynamicJsonDocument eventMessage = prepareEvent(deviceId, "currentTemperature", cause.c_str());
  JsonObject event_value = eventMessage["payload"]["value"];
  event_value["humidity"] = roundf(humidity * 10) / 10.0;
  event_value["temperature"] = roundf(temperature * 10) / 10.0;
  return sendEvent(eventMessage);
}

#endif

