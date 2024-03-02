#pragma once
#ifndef __COMMON_H__
#define __COMMON_H__

// Header containing any constants needed by the PayloadFSW

#include <Arduino.h>
#include <TimeLib.h>

namespace Common
{
  // Serial communication rate in bit/s
  const int SERIAL_BAUD = 9600

  // TO-DO: update the pin values to match actual config
  const byte VOLTAGE_PIN = 38;
  const byte PARA_SERVO_PIN = 22;
  const byte HS_SERVO_PIN = 23;
  const byte MAST_SERVO_PIN = 2;
  const byte CAMERA_PIN = 3;
  const byte AUDIO_BEACON_PIN = 6;

  // TO-DO: could be a better way to implement this feature?
  const float SEA_LEVEL = 1014.6f; //update this before launch
  const uint16_t TEAM_ID = 2054;

  // value addresses? need clarification on how/what these inits do
  const uint16_t BA_ADDR = 0; // base altitude
  const uint16_t PC_ADDR = 4; // packet count 
  const uint16_t ST_ADDR = 6; // states
  const String MS_ADDR = 17; // mission time
}

#endif