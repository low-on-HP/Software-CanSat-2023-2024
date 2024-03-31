// CanSat 2023-2024: PayloadFSW

/* To-Do: 

- scaffold XBee infrastructure
- packet counting? how?

*/

#include "Common.h" // Constants, Pin Identification
#include "Hardware.h" // Hardware setup, manipulation

void setup() {
  // Start Serial communication, if debugging
  SoftwareSerial Serial (Common::RXPIN, Common::TXPIN);
  Serial.begin(Common::SERIAL_BAUD);
  while (!Serial); // wait for serial connection
  Serial.println("Serial Connection Established.");

  // Initialize all components 
  Serial.println("Beginning Hardware Initialization...");
  Hardware::init();
  Serial.println("Hardware Initialized.");

  // List out all of the setup tasks, for later TO-DO

  // 

}

void loop() {
  // put your main code here, to run repeatedly:
}
