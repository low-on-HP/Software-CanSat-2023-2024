// Covers initialization of sensors, radios, and any functions that utilize hardware

#include "Common.h"
#include "Hardware.h"

#include <Wire.h>             // for I2C protocol
#include <Adafruit_BMP3XX.h>  // for BMP388 functionality
#include <Adafruit_BNO08x.h>  // for BNO085 functionality
#include "ms4250.h" // for airspeed sensor functionality

namespace Hardware
{

    /*Declare an MS4525DO Object*/
    bfs::Ms4525do pres;

  // setup BMP388 sensor
  void setupBMP()
  {
    // initialize BMP388 object
    Adafruit_BMP3XX bmp;

    // Check if BMP388 is connected
    if (!bmp.begin_I2C()) {
      Serial.println("Could not find BMP388, check wiring! womp womp.");
      while (1) { delay(10); } // Halt program if BMP388 is not found
    }

    // Misc. BMP388 Initialization - see Adafruit docs for specifics
    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_50_HZ);
  }

  // setup BNO085 sensor
  void setupBNO()
  {
    // init BNO object
    Adafruit_BNO08x bno(Common::BNO08X_RESET);
    sh2_SensorValue_t sensorValue;

    // Attempt init of bno I2C connection
    if (!bno08x.begin_I2C()) {
      // I2C connection failed, log error and halt
      Serial.println("Could not find BNO085, check wiring! boo womp.")
      while (1) { delay(10); }
    }
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

    // call BNO085 setup
    Serial.println("Initializing BNO085...")
    setupBNO();
  }

  //Performs the setup function on the airspeed sensor
  void setupAirSpeed() {
      /**Serisl to display data**/
      Serial.begin(9600);
      while (!Serial){}
      Wire.begin();
      Wire.setClock(400000); 

      //Setup the I2C address of Ox28, on bus 0, with a -1 to +1 PSI range
      pres.Config(&Wire, 0x28, 1.0f, -1.0f);
      //Starting the communication with the pressure transducer */
      if (!pres.Begin()) {
          Serial.println("Error communicating with sensor"); 
          while(1){}
      }
  }

  void loop() {
      //Read the sensor
      if (pres.Read()) {
          //Display the data
          Serial.print(pres.pres_pa(), 6); //Obtain the pressure readings from the sensor
          Serial.print("\t");
          Serial.print(pres.die_temp_c(), 6); //Might not be needed
          Serial.print("\n");
      }
      delay(10); //Apply the delay here
  }
}