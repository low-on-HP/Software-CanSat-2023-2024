// Covers initialization of sensors, radios, and any functions that utilize hardware

#include "Common.h"
#include "Hardware.h"

#include <Wire.h>             // for I2C protocol
#include <Adafruit_BMP3XX.h>  // for BMP388 functionality

namespace Hardware
{
  // initialize BMP388 object
  Adafruit_BMP3XX bmp;

  // setup BMP388 sensor
  void setupBMP()
  {
    // Check if BMP388 is connected
    if (!bmp.begin_I2C()) {
      Serial.println("Could not find BMP388, check wiring! womp womp.");
      while(1); // Halt program if BMP388 is not found
    }

    // Misc. BMP388 Initialization - see Adafruit docs for specifics
    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_50_HZ);
  }

  // Core function of the Boot-up/Initialization states. 
  // Performs set up for all sensors and other components, and does anything
  // that needs to be done before Standby state can be entered.
  void init()
  {
    // Start I2C connection
    Serial.println("Opening I2C Connection...")
    Wire.begin()

    // call BMP388 setup function
    Serial.println("Initializing BMP388...")
    setupBMP();
  }
}