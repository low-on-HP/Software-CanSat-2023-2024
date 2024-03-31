// CanSat 2023-2024: PayloadFSW

// To-Do: add to Hardware::init() for BNO, pitot | scaffold XBee infrastructure

#include "Common.h" // Constants, Pin Identification
#include "Hardware.h" // Hardware setup, manipulation

void setup() {
  // Start Serial communication, if debugging
  Serial.begin(Common::SERIAL_BAUD);
  while (!Serial); // wait for serial connection
  Serial.println("Serial Connection Established.");

  // Initialize all components 
  Serial.println("Beginning Hardware Initialization...");
  Hardware::init();
  Serial.println("Hardware Initialized.");

}

void loop() {
  // put your main code here, to run repeatedly:
}
