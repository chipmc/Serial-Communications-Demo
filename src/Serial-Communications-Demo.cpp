/* 
 * Project Serial1_Listener
 * Author: Chip McClelland  
 * Date: 12/12/2023
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "Serial1_Listener.h"

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

// setup() runs once, when the device is first turned on
void setup() {
  Serial.begin(115200);                       // Open serial port to communicate with host          
  waitFor(Serial.isConnected, 10000);         // Wait here until the serial port is opened

  Serial1_Listener::instance().setup();       // Setup the Serial1_Listener to listen to Serial1

  Log.info("Asking for Identification");      // Ask the Serial1 device for its identification
  Serial1.println("*IDN? \n");                // Send the *IDN? command to the Serial1 device
}

void loop() {
  Serial1_Listener::instance().loop();        // Loop the Serial1_Listener to listen to Serial1
}
