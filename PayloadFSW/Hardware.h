#pragma once
#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include "Common.h"

namespace Hardware
{
  extern Adafruit_BMP3XX bmp;

  void setupBMP();
  void init();
}

#endif