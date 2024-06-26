// Covers initialization of sensors, radios, and any functions that utilize hardware

#include "Common.h"
#include "Hardware.h"

#include <Wire.h>             // for I2C protocol
#include <Adafruit_BMP3XX.h>  // for BMP388 
#include <Adafruit_BNO08x.h>  // for BNO085 
#include "ms4250.h"           // for airspeed sensor 
#include <Adafruit_GPS.h>     // for GPS

namespace Hardware
{

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
    Serial.begin(115200); 
    while (!Serial)
      delay(10); // will pause Zero, Lenoardo, etc until serial console opens
    // init BNO object
    Adafruit_BNO08x bno08x(Common::BNO08X_RESET);
    sh2_SensorValue_t sensorValue;

    // Test and verify if the input signal reception occurs from the BNO chip
    Serial.println("Adafruit BNO8x test!");

    // Attempt init of bno I2C connection
    if (!bno08x.begin_I2C()) {
      // I2C connection failed, log error and halt
      Serial.println("Could not find BNO085, check wiring! boo womp.")
      while (1) { delay(10); }
    }

    // Printout if the BNO chip is found
    Serial.println("BNO8x Found!")

    // Once BNO chip is confirmed found, then detect and print out the information tied to the chip
    for (int n = 0; n < bno08x.prodIds.numEntries; n++) {
      Serial.print("Part "); 
      Serial.print(bno08x.prodIds.entry[n].swPartNumber); 

      Serial.print(": Version : "); 
      Serial.print(bno08x.prodIds.entry[n].swVersionMajor); 

      Serial.print("."); 
      Serial.print(bno08x.prodIds.entry[n].swVersionMinor); 

      Serial.print(" Build "); 
      Serial.println(bno08x.prodIds.entry[n].swBuildNumber);
    }

    bnoSetReports(); // call the specific sensor outputs for the BNO chip

    Serial.println("Reading events"); // Read specific events for what output can be generated by the BNO chip
    delay(1000); // Apply a delay for about 1000 ms
  }

  // Define the specific sensor outputs which we wish to receive for the BNO chip
  void bnoSetReports(void){ 
    Serial.println("Setting desired reports"); 
    if (!bno08x.enableReport(SH2_ACCELEROMETER)) {
      Serial.println("Could not enable accelerometer"); 
    }

    if (!bno08x.enableReport(SH2_GYROSCOPE_CALIBRATED)) {
      Serial.println("Could not enable gyroscope"); 
    }
    
    if (!bno08x.enableReport(SH2_MAGNETIC_FIELD_CALIBRATED)) {
      Serial.println("Could not enable magentic field calibrated"); 
    }

    if (!bno08x.enableReport(SH2_LINEAR_ACCELERATION)){
      Serial.println("Could not enable linear acceleration");
    }

    if (!bno08x.enableReport(SH2_GRAVITY)){
      Serial.println("Could not enable gravity vector");
    }

    if (!bno08x.enableReport(SH2_ROTATION_VECTOR)){
      Serial.println("Could not enable rotation vector");
    }

    if (!bno08x.enableReport(SH2_GEOMAGNETIC_ROTATION_VECTOR)){
      Serial.println("Could not enable geomagnetic rotation vector"); 
    }

    if (!bno08x.enableReport(SH2_GAME_ROTATION_VECTOR)){
      Serial.println("Could not enable game rotation vector");
    }

    if (!bno08x.enableReport(SH2_STEP_COUNTER)){
      Serial.println("Could not enable step counter"); 
    }

    if (!bno08x.enableReport(SH2_STABILITY_CLASSIFIER)){
      Serial.println("Could not enable stability classifier");
    }

    if (!bno08x.enableReport(SH2_RAW_ACCELEROMETER)){
      Serial.println("Could not enable raw accelerometer");
    }

    if (!bno08x.enableReport(SH2_RAW_GYROSCOPE)){
      Serial.println("Could not enable raw gyroscope");
    }

    if (!bno08x.enableReport(SH2_RAW_MAGNETOMETER)){
      Serial.println("Could not enable raw magnetometer");
    }

    if (!bno08x.enableReport(SH2_SHAKE_DETECTOR)){
      Serial.println("Could not enable shake detector");
    }

    if (!bno08x.enableReport(SH2_PERSONAL_ACTIVITY_CLASSIFIER)){
      Serial.println("Could not enable personal activity classifier");
    }
  }

  //Performs the setup function on the airspeed sensor
  void setupAirSpeed() 
  {
    /*Declare an MS4525DO Object*/
    bfs::Ms4525do pres;

    //Setup the I2C address of Ox28, on bus 0, with a -1 to +1 PSI range
    pres.Config(&Wire, 0x28, 1.0f, -1.0f);

    //Starting the communication with the pressure transducer */
    if (!pres.Begin()) {
      Serial.println("Error communicating with sensor"); 
      while(1){ delay(10); };
    }
  }

  // Setup GPS object / GPS Breakout
  void setupGPS()
  {
    // instantiate GPS object
    Adafruit_GPS gps(&Wire);

    // begin I2C connection
    gps.begin(0x10);
  }

  // Core function of the Boot-up/Initialization states. 
  // Performs set up for all sensors and other components, and does anything
  // that needs to be done before Standby state can be entered.
  void init()
  {
    // Start I2C connection
    Serial.println("Opening I2C Connection...");
    Wire.begin();
    Wire.setClock(400000);

    // call BMP388 setup function
    Serial.println("Initializing BMP388...");
    setupBMP();

    // call BNO085 setup
    Serial.println("Initializing BNO085...");
    setupBNO();

    // for calling the individual sensor output functions for the BNO, refer to how they are being used in the loop
    // to case switch and verify which specific sensor activity we want to enable, we will need to change it slightly if needed using a 
    // switch statement for a case-by-case basis
    // for basic setup, and calling the individual sensor activities, the setupBNO() function should suffice

    // call airspeed setup
    Serial.println("Initializing Airspeed Sensor...");
    setupAirSpeed();

    // call GPS setup
    Serial.println("Initializing GPS...");
    setupGPS();
  }

  // Define functions for buzzer operation
  void buzzer_on()
  {
    analogWriteFrequency(Common::AUDIO_BEACON_PIN, 4000);
    analogWrite(Common::AUDIO_BEACON_PIN, 128);
  }

  void buzzer_off()
  {
    analogWriteFrequency(Common::AUDIO_BEACON_PIN, 0);
    analogWrite(Common::AUDIO_BEACON_PIN, 0);
  }

  // keep for later, useful code but not for hardware setup

  // void loop() {
  //     //Read the sensor
  //     if (pres.Read()) {
  //         //Display the data
  //         Serial.print(pres.pres_pa(), 6); //Obtain the pressure readings from the sensor
  //         Serial.print("\t");
  //         Serial.print(pres.die_temp_c(), 6); //Might not be needed
  //         Serial.print("\n");
  //     }
  //     delay(10); //Apply the delay here
  // }
}